% cena(benzin, 2).
% cena(dizel, 1).
% max_goriva(600000).
% min_goriva(benzin, 150000).
% min_goriva(dizel, 0).
% max_goriva(dizel, 325000).
% max_goriva(benzin, 600000).

rafinerija(Zarada, X, Y) :-
    X :: 0 .. 600000,
    Y :: 0 .. 600000,
    X #>= 150000,
    Y #=< 325000,
    X + Y #=< 600000,
    2*Y #>=  X,
    labeling([maximize(2*X + 1*Y)], [X, Y]),
    Zarada is 2 * X + 1 * Y,
    write('Maksimalna zarada je: '), write(Zarada), write(' dolara'), nl,
    write('Kolicina benzina je: '), write(X), write(' galona'), nl,
    write('Kolicina dizela je: '), write(Y), write(' galona'), nl.
