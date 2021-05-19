% ! - cut operator, kada nadje prvo resenje,
% zaustavi se i ne trazi dalje
zameni(X, Y, XN, YN) :- XN is Y, YN is X.

clan0([X|_],X).
clan0([_|R],X):- write(R), clan(R,X).

% zeleno secenje (kada se vidi prva f-ja)
% nece se ni razmatrati druga
clan1([X|_],X) :- !.
clan1([_|R],X):- write(R), clan(R,X).

% ( If -> Then ; Else )
vece(A, B, X) :- ( A > B -> X = A ; X = B ).
vece(A, B, X) :- ( A > B -> X = A ; fail ).
