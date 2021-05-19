zbir10(X, Y) :- X in 1..10, Y in 1..10, X + Y #= 10, labeling(X).
parni(X) :- X in 1..100, X mod 2 #= 0, labeling(X).
