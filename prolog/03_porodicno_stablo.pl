%svojstva

musko(vladan).
musko(mladen).
musko(milos).
musko(marko).
musko(milan1).
musko(borivoje).
musko(milan).
musko(sloba).
musko(zivko).
zensko(slobodanka).
zensko(milica).
zensko(rada).
zensko(marina).
zensko(dragica).
zensko(silvija).
zensko(sandra).
zensko(milenka).

roditelj(marina, rada).
roditelj(marina, sloba).

roditelj(milica, rada).
roditelj(milica, sloba).

roditelj(milan, rada).
roditelj(milan, sloba).

roditelj(sloba, borivoje).
roditelj(sloba, slobodanka).

roditelj(mladen, vladan).
roditelj(mladen, silvija).

roditelj(sandra, vladan).
roditelj(sandra, silvija).

roditelj(marko, dragica).
roditelj(marko, milan1).

roditelj(milos, dragica).
roditelj(milos, milan1).

roditelj(dragica, slobodanka).
roditelj(dragica, borivoje).

roditelj(rada, zivko).
roditelj(rada, milenka).

roditelj(vladan, zivko).
roditelj(vladan, milenka).


otac(X, Y) :- musko(Y), roditelj(X, Y).
majka(X, Y) :- zensko(Y), roditelj(X, Y).
brat(X, Y) :- musko(Y), 
              majka(X, Z), majka(Y, Z),
              otac(X, Z1), otac(Y, Z1),
              X \= Y.

sestra(X, Y) :- zensko(Y), 
              majka(X, Z), majka(Y, Z),
              otac(X, Z1), otac(Y, Z1),
              X \= Y.

ujak(X, Y) :- majka(X, Z), brat(Z, Y).
tetka(X, Y) :- otac(X, Z), sestra(Z, Y).
deda(X, Y) :- roditelj(X, Z), roditelj(Z, Y), musko(Y).
baba(X, Y) :- roditelj(X, Z), roditelj(Z, Y), zensko(Y).
