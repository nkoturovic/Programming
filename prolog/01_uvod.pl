% Komande: help, compile('fajl'), load('fajl'), cl('fajl'), halt

voli(a, b).
voli(b, a) :- voli(a, b).

/*
[Termovi]:
    [Konstante]:
        [Atomi]: stringobi oblika 'abc ... ' najvise 1000 karakt.
        [Brojevi]: celi i realni
    [Promenljive]: Imena pocinju velikim slovom ili podvlakom

[Kompozitni (slozeni) termovi / strukture]:
    f(t1, t2, ... , tn) - f f-ja arnosi n, t1 ... tn termovi

[Program]: Sekvenca Hornovih klauza
[Hornova Klauza]: Cinjenica|Pravilo|Upit
    [Cinjenice i pravila]: BAZA ZNANJA
        [Cinjenica]: Atomicna formula oblika: p(t1, t2, ... , tn) - p predikat, t_i termi
        [Pravilo]: H :- B1, B2, .... , Bn  <=>  Vazi H ako vaze B1 i B2 i ...
    [Upit]: Konstrukcija kojom korisnik komunicira sa bazom znanja
*/

% Cinjenice
zivotinja(slon).
zivotinja(vuk).
zivotinja(zec).

% Cinjenice relacije
veci(slon, vuk).
veci(vuk, zec).

/* Upiti sa promenljivama:
?-  veci(slon, X)
    X = vuk
    X = zec

?-  veci(X, Y)
    X = slon
    Y = vuk %enter za kraj
*/

je_veci(X,Y):- veci(X,Z), veci(Z,Y).

% unifikacija (ujednacavanje), pokusaj poistovecivanja
uni(X, Y) :- X = Y.    % prihvata slobodne prom. i daje moguce vrednosti
jed(X, Y) :- X == Y.     % moraju biti konkretne vrednosti npr 2,2
arj(X, Y) :- X =:= Y.   % prihvata i aritmeticke izraze 2+1 =:= 4-1 
arnj(X, Y) :- X =/= Y.   % aritmeticki nisu jednaki

/* operatori 
<, =<. >, >=
+, -, *, /, //, mod, is
*/
