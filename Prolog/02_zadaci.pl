% 8.6
maksimum(A, B, M) :- A >= B, M is A, !.
maksimum(A, B, M) :- A < B, M is B, !.

% suma prvih N brojeva
suma(1, 1).
suma(N, S) :-  N > 0, N1 is N-1, suma(N1, S1), S is S1 + N.
% mora se koristiti is, suma(N-1, S1) ne bi radilo.


% suma prvih N parnih brojeva - preko sume
suma_n_parnih(N, S) :- N > 1, suma(N, S1), S is 2*S1.

% samostalno
suma_n_parnih1(2,2).
suma_n_parnih1(N, S) :- N > 2, N1 is N-1, suma_parnih(N1, S1), S is S1+2*N.

% suma parnih od 1..N 
suma_parnih(2,2).
suma_parnih(N, S) :- N > 2, N1 is N-2, suma_parnih(N1, S1), S is S1 + N.

% baza preslikavanja N -> Cifra
cifra(0, nula).           cifra(5, pet).   
cifra(1, jedan).          cifra(6, sest).  
cifra(2, dva).            cifra(7, sedam). 
cifra(3, tri).            cifra(8, osam).  
cifra(4, cetiri).         cifra(9, devet). 

% broj -> cifra_n, cifra_n-1, ... cifra_0
cifre(N) :- N < 1, !.
cifre(N) :- N1 is (N//10), O is (N mod 10), cifre(N1), cifra(O, X), write(X), nl.

paran(X) :- X mod 2 =:= 0.
paran1(X) :- (X mod 2 =:= 0 -> writeln('paran') ; writeln('neparan')).

% 8.7

% a)
sumaCifara(0, 0).
sumaCifara(N, SC) :- 
    N > 0,
    O is N mod 10,
    N1 is N // 10,
    sumaCifara(N1, SC1),
    SC is SC1 + O.


% b)
brojCifara(0, 0).
brojCifara(N, BC) :-
    N > 0,
    N1 is N // 10,
    brojCifara(N1, BC1),
    BC is 1 + BC1.

% c)
maxCifra(0, 0).
maxCifra(N, MC) :- 
    N > 0,
    O is N mod 10,
    N1 is N // 10,
    maxCifra(N1, MC1),
    (O > MC1 -> MC is O; MC is MC1).

% d)
sumaKvadrata(0, 0).
sumaKvadrata(N, SK) :- 
    N > 0,
    N1 is N-1,
    sumaKvadrata(N1, SK1),
    SK is SK1 + N * N.


fakt(0, 1).
fakt(N, F) :- 
    N > 0,
    N1 is N-1,
    fakt(N1, F1),
    F is N*F1.
