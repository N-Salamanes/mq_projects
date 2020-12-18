% ===========================================================
% Project: iKnow329
% Author:  Nigel Salamanes (43690599)
% Date:    October 2016
% ===========================================================

% -----------------------------------------------------------
% Use module
% -----------------------------------------------------------
:- use_module(library('readutil')).

% -----------------------------------------------------------
% Dynamic predicates
% -----------------------------------------------------------
:- dynamic student/2, teacher/1, kterm/6.

% -----------------------------------------------------------
% Style checking
% -----------------------------------------------------------
:- style_check([-singleton, -discontiguous]).

% -----------------------------------------------------------
% start/0
% -----------------------------------------------------------

start :-
	consult('kterms.pl'),
	consult('users.pl'),

	welcome,
	login(ID, Mode),
	(
	    Mode = student
	    ->
	    main_process_student(ID)
	    ;
	    Mode = teacher
	    ->
	    main_process_teacher(ID)
	    ),
	export_user_knowledge_base('users.pl').

% -----------------------------------------------------------
% -----------------------------------------------------------
% Your Code
% -----------------------------------------------------------
% -----------------------------------------------------------


% -----------------------------------------------------------
% read_input/1 , read input which returns an atom
% -----------------------------------------------------------
read_input(Input) :-
	read_line_to_codes(current_input, Codes), %get user input
	atom_codes(Atom, Codes), %convert input to atoms
	downcase_atom(Atom, DownCase), %make atoms all lower case
	normalize_space(atom(Input), DownCase). %take away space characters


% -----------------------------------------------------------
% welcome/0 , display welcome message
% -----------------------------------------------------------
welcome :-
	write('===================================================='),
	nl,
	write('Welcome to iKnow329 - an Intelligent Tutoring System'),
	nl,
	write('===================================================='),
	nl, nl.


% -----------------------------------------------------------
% login/2 , enter ID which sets the mode (student or teacher)
% -----------------------------------------------------------
login(ID, Mode) :-
	write('Enter your ID:'),
	nl,
	read_input(IDstr),
	(
	    student(IDstr, _) -> Mode = student,
		 ID = IDstr;
	    teacher(IDstr) -> Mode = teacher
	),
	nl.


% -----------------------------------------------------------
% main_process_student/1 , main predicate for student
% -----------------------------------------------------------
main_process_student(ID) :-
	write('Choose one of the following difficulty levels: easy, medium, or hard.'),
	nl,
	read_input(Difficultystr), % get the difficulty
	nl,
	write('Choose one of the following topics: parsing, probability theory, Prolog.'),
	nl,
	read_input(Topicstr), %get the topic
	nl,
	QNum = 0, InitScore = 0, % initial variables
	askQuestion(Topicstr, Difficultystr, QNum, InitScore, EndScore), % recursive predicate
	write('Congratulations: you got '), write(EndScore), write(' marks.'), nl, nl,
	%add results to knowledge base
	assert(student(ID, [Topicstr, Difficultystr, EndScore])),
	%run again or not
	write('Another run? yes/no'), nl,
	read_input(AnotherRun), nl, !, % cut here so we can't backtrack
	=(AnotherRun, 'yes') -> main_process_student(ID)
	;
	write('Thanks for using iKnow329'), nl.


% -----------------------------------------------------------
% askQuestion/5 , ask and retrieve answer [as student]
% -----------------------------------------------------------
askQuestion(Topic, Level, QNum, Score, EndScore) :-
	findall(X , kterm(_, topic(Topic), level(Level), _, _, _), Questions),
	length(Questions, NumOfQuestions), %retrieve how many questions there are
	QNum = NumOfQuestions, !, %end of asking questions, dont backtrack
	EndScore is Score.

askQuestion(Topic, Level, QNum, Score, EndScore) :-
	QuestionNum is QNum + 1,
	kterm(number(QuestionNum),%unify kterm with variables
	      topic(Topic),
	      level(Level),
	      question(Qtype,Qquestion,Qmark),
	      answer(Answer, AnswerList),
	      hint(Hint, HintDeduct)),
	write(QuestionNum), write(': '),write(Qquestion), %write the question
	nl,
	read_input(UserAnswer), nl,
	%disjunction, true/false for users answer
	(   %check if answer is correct
	    check_user_answer(UserAnswer, AnswerList)-> true,
	    %correct answer
	    NewScore is Score + Qmark,
	    askQuestion(Topic, Level, QuestionNum, NewScore, EndScore)
	    ; %DISJUNCTION

            %incorrect answer

	    %check question type
	    (
		=(Qtype, 'wh') -> get_hint(HintAnswer),
		(   %DISJUNCTION FOR HINT
		    %GET HINT, answered yes
		    =(HintAnswer, 'yes'),
		    write('Hint: '), write(Hint), nl,nl,
		    write('Try to answer the following question again:'),nl,nl,
		    write(QuestionNum), write(': '), write(Qquestion),nl,
		    %check if 2nd answer is correct
		    read_input(UserAnswer2), nl,
		    (	check_user_answer(UserAnswer2, AnswerList) -> true,
				      % correct 2nd answer
				      NewScore is Score + Qmark - HintDeduct,
		                      askQuestion(Topic, Level, QuestionNum, NewScore, EndScore)
			    ;
		    %2nd answer wrong
		    askQuestion(Topic, Level, QuestionNum, Score, EndScore))
		    ;
		    %'no' or anything else than 'yes'
		    askQuestion(Topic, Level, QuestionNum, Score, EndScore)
		)
	    ;%DISJUNCTION, QTYPE 'wh' or not
	    %NOT a 'wh' question
	    askQuestion(Topic, Level, QuestionNum, Score, EndScore))
	).


% -----------------------------------------------------------
% get_hint/1 , asks the user if they want a hint or not
% -----------------------------------------------------------
get_hint(HintAnswer) :-
	write('Would you like a hint? yes/no'), nl,
	read_input(HintAnswer), nl.


% -----------------------------------------------------------
% check_user_answer/2 , checks the students answer
% -----------------------------------------------------------
check_user_answer(UserAnswer, AnswerList) :-
	(%disjunction(s)
    %check if input matches list of combinations
    atomic_list_concat(UserAnswerList, ' ', UserAnswer),%list of strings to atoms
    check_list(UserAnswerList, AnswerList) ->
    write('Your answer is correct'),
    nl,nl;
    write('Your answer is incorrect'),
    nl,nl,
    false
).


% -----------------------------------------------------------
% check_list/2 , compares user answer to list combination
% -----------------------------------------------------------
check_list(UserAnswerList, AnswerList) :-
	[ALHead|ALTail] = AnswerList,
	(%disjunction
	check_list_indiv(UserAnswerList, ALHead);
	check_list(UserAnswerList, ALTail)
        ).
% -----------------------------------------------------------
% check_list_indiv/2 , compares user answer atom by atom
% -----------------------------------------------------------
check_list_indiv(_, []).
check_list_indiv(UserAnswerList, AnswerList) :-
	[ALHead|ALTail] = AnswerList,
	member(ALHead, UserAnswerList),
	check_list_indiv(UserAnswerList, ALTail).




% -----------------------------------------------------------
% main_process_teacher/1 , main predicate for teacher
% -----------------------------------------------------------
main_process_teacher(ID) :-
	get_set_inspect(StudentID), nl, %get and set studentid for viewing
	print_student_info(StudentID), %print student information

	write('Another student? yes/no'),nl,
	read_input(AnotherStudent),nl, % finish or do another student
	(
	    =(AnotherStudent, 'yes') -> !, main_process_teacher(ID)
	    ;
	    write('Thanks for using iKnow329'), nl
	).



% -----------------------------------------------------------
% get_set_inspect/1 , retrieve list of students and sets one for viewing
% -----------------------------------------------------------
get_set_inspect(StudentID) :-
	findall(X, student(X,_), StudentList),% get all the students
	sort(StudentList, StudentListSorted), % sort the students alphabetically
	write('Which one of the following students would you like to inspect: '),
	print_student_list(StudentListSorted), nl,
	read_input(StudentID).


% -----------------------------------------------------------
% print_student_list/1 , prints out the list of available students
% -----------------------------------------------------------
print_student_list([]). % base case, terminating condition
print_student_list(StudentList) :-
	[X|Xs] = StudentList, % create head/tail
	write(X), % print head
	(   Xs = [],
	    write('.');
	write(', ')),
	print_student_list(Xs). %recursively call with tail


% -----------------------------------------------------------
% print_student_info/1 , print out available info about student
% -----------------------------------------------------------
print_student_info(StudentID) :-
	write('Student: '), write(StudentID), nl,nl,
	findall(X, student(StudentID, X), StudentInfo),
	[StudentInfoList] = StudentInfo,
	print_student_info_indiv(StudentInfoList).

% -----------------------------------------------------------
% print_student_info_indiv/1 , print individual atoms of info
% -----------------------------------------------------------
print_student_info_indiv([]) :- !.
print_student_info_indiv(StudentInfoList) :-
	[Head|Tail] = StudentInfoList,
	[X, Y, Z] = Head,
	write('Topic: '), write(X),nl,
	write('Level: '), write(Y),nl,
	write('Marks: '), write(Z),nl, nl,
	print_student_info_indiv(Tail).



% -----------------------------------------------------------
% export_user_knowledge_base/1 , updates the knowledge base file
% -----------------------------------------------------------
export_user_knowledge_base(File) :-
	%open the file to write to
	open(File, write, Stream),
	findall(X, student(X,_), StudentListWDups), %get all the students
	sort(StudentListWDups, StudentList), % remove duplicates
	append_user(StudentList, Stream), %get and write all the students data

	findall(X, teacher(X), TeacherList), %get all the teachers
	write_teachers(TeacherList, Stream), %write teachers to database

	clean_knowledge_base, % clear temp knowledge base
	close(Stream). %close tream


% -----------------------------------------------------------
% append_user/2 , retrieve and write all student data to file
% -----------------------------------------------------------
append_user([], Stream). % when no more students to process
append_user(UserList, Stream) :-
	[User|RemainingUsers] = UserList, %get individual user
	findall(Results, student(User, Results), ResultList), %get all the results for user
	[Result|RemainingResults] = ResultList, % split result list
	append(Result, RemainingResults, ResultAppended), %combine all the results
	write(Stream, student(User, ResultAppended)), %write the user to file
	write(Stream, '.'),
	nl(Stream),
	%process next user
	append_user(RemainingUsers, Stream).


write_teachers([], Stream). % when no more teachers
write_teachers(TeacherList, Stream) :-
	[Teacher|RemainingTeachers] = TeacherList,
	write(Stream, teacher(Teacher)),
	write(Stream, '.'),
	nl(Stream),
	write_teachers(RemainingTeachers, Stream).





% -----------------------------------------------------------
% clean_knowledge_base/0 , cleans the knowledge base
% -----------------------------------------------------------
clean_knowledge_base :-
	retractall(student(_,_)),
	retractall(teacher(_)),
	retractall(kterm(_, _, _, _, _, _)).






