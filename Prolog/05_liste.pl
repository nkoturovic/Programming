% unifikacija
% [X, Y, Z] = [1, 2, 3]
%
%X = .(1, .(2, []))
%X = [1,2]

% red cut - biti oprezan
% ovde dodje bazni slucaj, jer ispod nema telo
sadrzi([G|_], G) :- !.
sadrzi([_|T], X) :- sadrzi(T, X).

duzina([_|T], N) :- duzina(T,N1), N is N1+1.
duzina([], N) :- N is 0, !.

% dodaj na pocetak
dodaj_na_pocetak(L, E, [E|L]).
dodaj_na_pocetak1(L, E, NL) :- append([E], L, NL).
dodaj_na_kraj(L, E, NL) :- append(L, [E], NL).
obrisi_prvi([_|T], T).

obrisi_poslednji([_], []) :- !.
obrisi_poslednji([H|T], L) :- obrisi_poslednji(T,T1), append([H], T1, L).

% brise sva pojavljivanja elementa X u listi L
obrisi(_, [], []).
obrisi(X, [X|T], NL) :- obrisi(X, T, NL), !.
obrisi(X, [H|T], NL) :- obrisi(X, T, NLN), append([H], NLN, NL).

% nesto jednostavnije i bolje resenje
obrisi1(_, [], []).
obrisi1(X, [X|T], NL) :- obrisi(X, T, NL), !.
obrisi1(X, [H|T], [H|T1]) :- obrisi(X, T, T1).


obrisi_prvo(X, [X|T], T) :- !.
obrisi_prvo(X, [H|T], NL) :- obrisi_prvo(X, T, NL1), append([H], NL1, NL).

obrisiK([_|T], 1, T) :- !.
obrisiK([H|T], K, NL) :- K > 1, K1 is K-1, obrisiK(T, K1, NL1), append([H], NL1, NL). 
