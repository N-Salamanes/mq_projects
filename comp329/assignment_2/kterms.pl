% -----------------------------------------------------------
% kterm/6
% -----------------------------------------------------------


% -----------------------------------------------------------
% PROLOG/EASY
% -----------------------------------------------------------
kterm(number(1),
      topic(prolog),
      level(easy),
      question(wh, 'What does Prolog stand for?', 1),
      answer('Programming in Logic', [[programming, in, logic], [logic, programming]]),
      hint('Pro... in Log...', 0.5)).
kterm(number(2),
      topic(prolog),
      level(easy),
      question(yn, 'Is Prolog a procedural programming language?', 1),
      answer('no', [[no], [nope], [nah]]),
      hint(nil, nil)).
kterm(number(3),
      topic(prolog),
      level(easy),
      question(yn, 'Does the following unification succeed: [a, [b]|[c, d]]=[X, Y, Z]?', 1),
      answer('yes', [[yes], [yep], [sure]]),
      hint(nil, nil)).
kterm(number(4),
      topic(prolog),
      level(easy),
      question(wh, 'What is the most common data structure in Prolog?', 1),
      answer('lists', [[list], [lists]]),
      hint('It has a head and a tail.', 0.5)).
kterm(number(5),
      topic(prolog),
      level(easy),
      question(wh, 'Why is Prolog good for AI programming?', 1),
      answer('Because Prolog is good at pattern matching', [[pattern, matching], ['pattern-matching']]),
      hint('Regular expressions provide a similar functionality.', 0.5)).


% -----------------------------------------------------------
% PROLOG/MEDIUM
% -----------------------------------------------------------
kterm(number(1),
      topic(prolog),
      level(medium),
      question(wh, 'How does Prolog solve its queries?', 2),
      answer('Through backtracking', [[backtracking], [back, tracking], [back-tracking]]),
      hint('It goes backwards and forwards', 1)).
kterm(number(2),
      topic(prolog),
      level(medium),
      question(yn, 'Does append([a,b,c], [H], [a,b,c,d,e]). return false?', 2),
      answer('Programming in Logic', [[yes], [yeah], [yeh],[yep], [sure]]),
      hint(nil, nil)).
kterm(number(3),
      topic(prolog),
      level(medium),
      question(wh, 'What is the operator for: Negation as failure?', 2),
      answer('\\+', [[\+], [backslash, plus], [back-slash, plus]]),
      hint('Two characters, first is: \\', 1)).
kterm(number(4),
      topic(prolog),
      level(medium),
      question(wh, 'What do prolog variable names start with?', 2),
      answer('A capital letter', [[capital, letter], [capital, letters], [capital], [capitals], [upper, case], [upper-case]]),
      hint('Big rather than small', 1)).
kterm(number(5),
      topic(prolog),
      level(medium),
      question(yn, 'Are anonymous variables bound?', 2),
      answer('Anonymous variables are not bound', [[no], [nah], [nope], [not, bound]]),
      hint(nil, nil)).


% -----------------------------------------------------------
% PROLOG/HARD
% -----------------------------------------------------------
kterm(number(1),
      topic(prolog),
      level(hard),
      question(wh, 'What kind of cut changes the meaning of the program?', 3),
      answer('Red cuts change the meaning of the program', [[red], [red, cut],[red, cuts], [red-cuts]]),
      hint('It is a colour', 1.5)).
kterm(number(2),
      topic(prolog),
      level(hard),
      question(yn, 'Does DCG rules have the form: head --> body ?', 3),
      answer('Yes it does', [[yes], [yeah], [yeh], [yep], [sure]]),
      hint(nil, nil)).
kterm(number(3),
      topic(prolog),
      level(hard),
      question(wh, '[a, b, [c|D], E, [f, g, h], _, i] = [A1, A2, [A3|A4], e, [A5|A6], A7|A8].  What does A5 unify with?', 3),
      answer('It unifies with: f', [[f]]),
      hint('Its close to: A6=[g,h]', 1.5)).
kterm(number(4),
      topic(prolog),
      level(hard),
      question(wh, 'What is the system predicate for retracting from the knowledge base?', 3),
      answer('The system predicate: retract', [[retract]]),
      hint('The opposite of tract', 1.5)).
kterm(number(5),
      topic(prolog),
      level(hard),
      question(wh, 'What kind of negation is negation as failure?', 3),
      answer('It is weak negation', [[weak], [weak, negation]]),
      hint('It is either weak or strong', 1.5)).


% -----------------------------------------------------------
% PARSING/EASY
% -----------------------------------------------------------
kterm(number(1),
      topic(parsing),
      level(easy),
      question(wh, 'What happens after the parser decides the input string is described by the grammar?', 1),
      answer('It assigns a structure to the input string', [[assign, structure], [assigns, structure], [assign, structures], [assigns, structures]]),
      hint('It assigns something', 0.5)).
kterm(number(2),
      topic(parsing),
      level(easy),
      question(wh, 'In a simple DCG, replace the asterisks: s *** np, vp.', 1),
      answer('-->', [[-->]]),
      hint('some characters revealed: --*', 0.5)).
kterm(number(3),
      topic(parsing),
      level(easy),
      question(wh, 'Within DCG parsing, top down parsing is?', 1),
      answer('It is predictive or hypothesis driven', [[predictive],[hypothesis, driven]]),
      hint('pre******* OR hypo****** dri***', 0.5)).
kterm(number(4),
      topic(parsing),
      level(easy),
      question(wh, 'What kind of rules have a problem with TOP DOWN parsing?', 1),
      answer('Left-recursive rules have a problem', [[left, recursive, rules], [left-recursive, rules]]),
      hint('[DIRECTION]-recursive rules have a problem', 0.5)).
kterm(number(5),
      topic(parsing),
      level(easy),
      question(wh, 'What problem does simple BOTTOM UP parsers have?', 1),
      answer('They can not handle empty categories', [[empty, categories], [empty, category]]),
      hint('Empty [things] have a problem', 0.5)).


% -----------------------------------------------------------
% PARSING/MEDIUM
% -----------------------------------------------------------
kterm(number(1),
      topic(parsing),
      level(medium),
      question(wh, 'What kind of tree does a DCG return?', 2),
      answer('It returns a syntactic tree', [[syntactic, tree], [syntactic, trees], [syntax, tree], [syntax, trees], [syntax]]),
      hint('Rules, principles and processes that govern the structure of sentences', 1)).
kterm(number(2),
      topic(parsing),
      level(medium),
      question(wh, 'What kind of grammar does DCG specify?', 2),
      answer('Natural language grammars', [[natural, language], [natural]]),
      hint('Its a type of language grammar', 1)).
kterm(number(3),
      topic(parsing),
      level(medium),
      question(wh, 'How many arguments should DCG have when translated into a Prolog program?', 2),
      answer('Two arguments', [[two], ['2']]),
      hint('Its more than one', 1)).
kterm(number(4),
      topic(parsing),
      level(medium),
      question(yn, 'Can syntactic features be used to constrain the grammar?', 2),
      answer('Yes it can', [[yes], [yeah], [yep]]),
      hint(nil, nil)).
kterm(number(5),
      topic(parsing),
      level(medium),
      question(wh, 'What kind of logic is Prolog based on?', 2),
      answer('It is based on Horn clause logic', [[horn, clause, logic], [horn, clause]]),
      hint('Horn [something] logic', 1)).


% -----------------------------------------------------------
% PARSING/HARD
% -----------------------------------------------------------
kterm(number(1),
      topic(parsing),
      level(hard),
      question(yn, 'Do natural language aspects involve: syntax, semantics, pragmatics?', 3),
      answer('Yes it does', [[yes], [yeah], [yep]]),
      hint(nil, nil)).
kterm(number(2),
      topic(parsing),
      level(hard),
      question(yn, 'Can subsets of natural language be translated into FOL and Horn clause logic via DCG?', 3),
      answer('Yes it does', [[yes], [yeah], [yep]]),
      hint(nil, nil)).
kterm(number(3),
      topic(parsing),
      level(hard),
      question(wh, 'What should be the result for the query: expr(Tree, [15, +, 3, -], []). ?', 3),
      answer('It should return false', [[false], [no, unify], [no, unification],[nothing]]),
      hint('Its missing something', 1.5)).
kterm(number(4),
      topic(parsing),
      level(hard),
      question(yn, 'Is a DCG context free grammar?', 3),
      answer('The structure', [[yes], [yeah], [yep]]),
      hint(nil, nil)).
kterm(number(5),
      topic(parsing),
      level(hard),
      question(wh, 'What kind of algorithm does a shift-reduce parser use?', 3),
      answer('Bottom-up algorithm', [[bottom, up], [bottom-up]]),
      hint('Either top-bottom or bottom-up', 1.5)).


% -----------------------------------------------------------
% PROBABILITY/EASY
% -----------------------------------------------------------
kterm(number(1),
      topic(probability),
      level(easy),
      question(wh, 'What does the t mean in: A(subscript)t ?', 1),
      answer('It means time', [[time]]),
      hint('Seconds, minutes, hours', 0.5)).
kterm(number(2),
      topic(probability),
      level(easy),
      question(yn, 'Does default/nonmonotonic logic work unless contradicted by evidence?', 1),
      answer('Yes it does', [[yes], [yep], [yeah]]),
      hint(nil, nil)).
kterm(number(3),
      topic(probability),
      level(easy),
      question(wh, 'For the Monte Hall problem, is it better to switch or stay after choice 1?', 1),
      answer('It is better to switch', [[switch]]),
      hint('Two choices is better than one', 0.5)).
kterm(number(4),
      topic(probability),
      level(easy),
      question(wh, 'What is the name of any subset of the sample space?', 1),
      answer('It is called an event', [[event]]),
      hint('One particular thing', 0.5)).
kterm(number(5),
      topic(probability),
      level(easy),
      question(wh, 'What is the name of the subset of the sample space of a simple event?', 1),
      answer('It is called a singleton', [[singleton]]),
      hint('One, Un, Ein, Uno', 0.5)).


% -----------------------------------------------------------
% PROBABILITY/MEDIUM
% -----------------------------------------------------------
kterm(number(1),
      topic(probability),
      level(medium),
      question(yn, 'Can probabilities of outcomes be zero(0)?', 2),
      answer('No it cant be', [[no], [nah], [nope], [cant]]),
      hint(nil, nil)).
kterm(number(2),
      topic(probability),
      level(medium),
      question(wh, 'What should be the sum of all outcomes, the total probability mass?', 2),
      answer('It should be one(1)', [[one], ['1']]),
      hint('Its to normalise everything and keep it in ratio', 1)).
kterm(number(3),
      topic(probability),
      level(medium),
      question(yn, 'Using Bayes rule, can P(E)=0 be defined?', 2),
      answer('No it is undefined', [[no], [nah], [nope], [undefined]]),
      hint(nil, nil)).
kterm(number(4),
      topic(probability),
      level(medium),
      question(yn, 'Are two events X and Y always independent?', 2),
      answer('No it is not', [[no], [nah], [nope]]),
      hint(nil, nil)).
kterm(number(5),
      topic(probability),
      level(medium),
      question(yn, 'After normalisation, is the new probability function denoted by: P(.|E)?', 2),
      answer('Yes it is', [[yes], [yeah], [yep]]),
      hint(nil, nil)).



% -----------------------------------------------------------
% PROBABILITY/HARD
% -----------------------------------------------------------
kterm(number(1),
      topic(probability),
      level(hard),
      question(wh, 'Enter in the missing character for Prior Probability, P(*)', 3),
      answer('It is denoted by: P(A)', [[a]]),
      hint('In the absence of other information', 1.5)).
kterm(number(2),
      topic(probability),
      level(hard),
      question(wh, 'Enter in the missing character for Conditional Probability P(*|*)', 3),
      answer('It is denoted by: P(A|B)', [[a, b], [ab]]),
      hint('probability of * given that ALL we know is *', 1.5)).
kterm(number(3),
      topic(probability),
      level(hard),
      question(wh, 'In belief networks, what does each node consist of?', 3),
      answer('It consists of random variables', [[random, variables]]),
      hint('Anything, chaotic', 1.5)).
kterm(number(4),
      topic(probability),
      level(hard),
      question(yn, 'Is a belief network a complete and non-redundant representation of domain?', 3),
      answer('Yes it is', [[yes], [yep], [yeah]]),
      hint(nil, nil)).
kterm(number(5),
      topic(probability),
      level(hard),
      question(wh, 'What kind of graph is a belief network?', 3),
      answer('It is a Directed Acyclic Graph', [[directed, acyclic]]),
      hint('Its directed, but theres more to it', 1.5)).


















