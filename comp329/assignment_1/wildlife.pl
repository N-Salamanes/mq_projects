solve_wildlife :-
	%structure
	S = [_, _, _,
	     _, _, _,
	     _, _, _],
	%animals
	member([_,lion], S),
	member([_,platypus], S),
	member([_,zebra], S),
	member([_,ape], S),
	member([_,tiger], S),
	member([_,giraffe], S),
	member([_,camel], S),
	member([_,koala], S),
	member([_,elephant], S),
	north_of([_,lion], [_,platypus], S),
	south_of([_,lion], [_,zebra], S),
	west_of([_,ape], [_,tiger], S),
	east_of([_,koala], [_,lion], S),
	immediate_south_east_of([_,giraffe], [_,camel], S),
	immediate_south_west_of([_,elephant], [_,koala], S),
	set_position(1, S),
	print_info(1, S), !.

%output with formatting
print_info(_, []).
print_info(X, Y) :-
	X = 4,
	Xnew = 1,
	nl,
	print_info(Xnew, Y), !.
print_info(X, [H|T]) :-
	write(H),
	Xnew is X+1,
	print_info(Xnew, T).

%sets the position for the animals
set_position(_, []).
set_position(X, [H|T]) :-
	nth1(1, H, X),
	Xnew is X+1,
	set_position(Xnew, T).

% north_of shows all possibilities which includes "immediates of" and
% not immediate of
north_of([_|X], [_|Y], S) :-
	S = [[_|A], [_|B], [_|C],
	     [_|D], [_|E], [_|F],
	     [_|G], [_|H], [_|I]],
	(%start of disjunction
		(%top row
		X = A,
		Y = D);
		(
		X = B,
		Y = E);
		(
		X = C,
		Y = F);
		(%mid row
		X = D,
		Y = G);
		(
		X = E,
		Y = H);
		(
		X = F,
	        Y = I);
		(%top and bot (not immediate of)
		X = A,
		Y = G);
		(
		X = B,
		Y = H);
		(
		X = C,
		Y = I)).

% south_of shows all possibilities which includes "immediates of" and
% not immediate of
south_of([_|X], [_|Y], S) :-
	S = [[_|A], [_|B], [_|C],
	     [_|D], [_|E], [_|F],
	     [_|G], [_|H], [_|I]],
	(%start of disjunction
		(%mid row
		X = D,
		Y = A);
		(
		X = E,
		Y = B);
		(
		X = F,
		Y = C);
		(%bot row
		X = G,
		Y = D);
		(
		X = H,
		Y = E);
		(
		X = I,
	        Y = F);
		(%top and bot (not immediate of)
		X = G,
		Y = A);
		(
		X = H,
		Y = B);
		(
		X = I,
		Y = C)).
% east_of shows all possibilities which includes "immediates of" and
% not immediate of
east_of([_|X], [_|Y], S) :-
	S = [[_|A], [_|B], [_|C],
	     [_|D], [_|E], [_|F],
	     [_|G], [_|H], [_|I]],
        (%start of disjunction
		(%mid row
		X = B,
		Y = A);
		(
		X = E,
		Y = D);
		(
		X = H,
		Y = G);
		(%right row
		X = C,
		Y = B);
		(
		X = F,
		Y = E);
		(
		X = I,
	        Y = H);
		(%right and left (not immediate of)
		X = C,
		Y = A);
		(
		X = F,
		Y = D);
		(
		X = I,
		Y = G)).
% west_of shows all possibilities which includes "immediates of" and
% not immediate of
west_of([_|X], [_|Y], S) :-
	S = [[_|A], [_|B], [_|C],
	     [_|D], [_|E], [_|F],
	     [_|G], [_|H], [_|I]],
	(%start of disjunction
		(%mid row
		X = A,
		Y = B);
		(
		X = D,
		Y = E);
		(
		X = G,
		Y = H);
		(%right row
		X = B,
		Y = C);
		(
		X = E,
		Y = F);
		(
		X = H,
	        Y = I);
		(%right and left (not immediate of)
		X = A,
		Y = C);
		(
		X = D,
		Y = F);
		(
		X = G,
		Y = I)).

% immediate_south_east shows all possibilities that are immediately
% south east of each other
immediate_south_east_of([_|X], [_|Y], S) :-
	S = [[_|A], [_|B], [_|_],
	     [_|D], [_|E], [_|F],
	     [_|_], [_|H], [_|I]],
	(%start of disjunction
		(%top and mid
		X = E,
		Y = A);
		(
		X = F,
		Y = B);
		(%mid and bottom
		X = H,
		Y = D);
		(
		X = I,
		Y = E)).

% immediate_south_west shows all possibilities that are immediately
% south west of each other
immediate_south_west_of([_|X], [_|Y], S) :-
	S = [[_|_], [_|B], [_|C],
	     [_|D], [_|E], [_|F],
	     [_|G], [_|H], [_|_]],
	(%start of disjunction
		(%top and mid
		X = D,
		Y = B);
		(
		X = E,
		Y = C);
		(%mid and bottom
		X = G,
		Y = E);
		(
		X = H,
		Y = F)).
