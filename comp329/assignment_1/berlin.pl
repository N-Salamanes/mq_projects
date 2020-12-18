%rank(Name, Job, CountryName, Rank).
solve(S) :-
	S = [_, _, _],
	%given variable and constants
	member([sam, _, _, _], S),
	member([pedro, _, france, _], S),
	member([yusuf, engineer, _, _], S),
	member([_, cook, _, _], S),
	member([_, professor, _, 1], S),
	member([_, _, australia, _], S),
	member([_, _, germany, _], S),
	member([_, _, _, 2], S),
	member([_, _, _, 3], S),
	%my constraints
	first([_, _, _, 1], S),
	arrive_before([yusuf, _, _, _],[_, _, australia, _], S), !.



first(X, [X|_]) :-
	nth1(4, X, Elem),
	Elem = 1.

arrive_before(X, Y, [X, Y|_]) :-
	nth1(4, X, Elem1),
	nth1(4, Y, Elem2),
	Elem1 < Elem2.

arrive_before(X, Y, [_|Z]) :-
	arrive_before(X, Y, Z).
