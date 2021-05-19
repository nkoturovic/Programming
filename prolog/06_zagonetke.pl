clan(X, [X|_]).
clan(X, [_|T]) :- clan(X, T).

% m(muskarac, zena, musko_kostim, zensko_kostim, vreme_dolaska).

maskembal(L) :- L = [
m(_,_,_,_,1),
m(_,_,_,_,2),
m(_,_,_,_,3),
m(_,_,_,_,4) ],
clan(m(marko,_,_,_,_), L),
clan(m(vasa,_,_,_,VaStig), L),
clan(m(pera,_,_,_,_), L),
clan(m(laza,_,_,_,LazaStig), L),
clan(m(_,bojana,_,_,BojanaStig), L),
clan(m(_,ana,_,_,AnaStig), L),
clan(m(_,marija,_,_,MarijaStig), L),
clan(m(_,ivana,_,_,IvanaStig), L),
clan(m(_,_,medved,_,MedvStig), L),
clan(m(_,_,princ,_,PrStig), L),
clan(m(_,_,'paja patak',_,_), L),
clan(m(_,_,betmen,_,_), L),
clan(m(pera,ZVest,'paja patak',vestica,_), L),  %4 
clan(m(_,_,_,snezana,SnezStig), L),                
clan(m(_,_,_,macka,_), L),                         
clan(m(_,_,_,ciganka,CigStig), L),              %2 
clan(m(marko,_,_,macka,3), L),                  %1 
\+(clan(m(vasa,_,_,_,1), L)),                   %3 
\+(clan(m(_,ana,betmen,_,_), L)),               %6 
\+(clan(m(_,_,betmen,ciganka,_), L)),           %6 
MedvStig =< 2,                                  %1 
VaStig < PrStig,                                %3 
ZVest \= bojana,                                %4 
MarijaStig > LazaStig,                          %5 
LazaStig < BojanaStig,                          %5 
CigStig < AnaStig,                              %6 
SnezStig > IvanaStig.                           %7 


% 8.31
% sadrzi radi isto sto i clan iznad
sadrzi([X|_], X).
sadrzi([_|T], X) :- sadrzi(T,X).

desno([H1,H2|_], H2, H1) :- !.
desno([_|T], H1, H2) :- desno(T,H1,H2).

levo([H1,H2|_], H1, H2) :- !.
levo([_|T], H1, H2) :- levo(T,H1,H2).

pored(L, H1, H2) :- levo(L,H1,H2);desno(L,H1,H2).

% k(boja, nacionalnost, pice, jelo, ljubimac).
kuce(L) :- L = [
    k(_,norvezanin,_,_,_),
    k(plava,_,_,_,_),
    k(_,_,mleko,_,_),
    k(_,_,_,_,_),
    k(_,_,_,_,_)],
    sadrzi(L, k(crvena,englez, _, _, _)),
    sadrzi(L, k(zelena,_,kafa,_,_)),
    sadrzi(L, k(bela,_, _, _, _)),
    sadrzi(L, k(zuta,_, _, pica, _)),
    sadrzi(L, k(_,spanac, _, _,pas)),
    sadrzi(L, k(_,ukrajinac, caj, _, _)),
    sadrzi(L, k(_,japanac, _, susi, _)),
    sadrzi(L, k(_,_,_,spagete,puz)),
    sadrzi(L, k(_,_,_,piletina,_)),
    sadrzi(L, k(_,_,_,pica,_)),
    sadrzi(L, k(_,_,_,_,lisica)),
    sadrzi(L, k(_,_,_,_,konj)),
    sadrzi(L, k(_,_,narandza,brokoli,_)),
    sadrzi(L, k(_,_,_,_,zebra)),
    sadrzi(L, k(_,_,voda,_,_)),
    desno(L, k(zelena,_,_,_,_),k(bela,_,_,_,_)),
    pored(L, k(_,_,_,piletina,_),k(_,_,_,_,lisica)),
    pored(L, k(_,_,_,pica,_),k(_,_,_,_,konj)).

zagonetka(Z,V) :- kuce(L), sadrzi(L, k(_,Z,_,_,zebra)), sadrzi(L, k(_,V,voda,_,_)).

%%%%%%%%%%%%%%%%%%%%%%%%%
%   L zagonetka(X, Y).  %   
%   X = japanac         %
%   Y = norvezanin      %
%%%%%%%%%%%%%%%%%%%%%%%%%


%  PP-2018-jun2

% i(ime, prezime, igra, grickalica)

prijatelji(L) :- L = [
i(_, _, _, _),
i(_, _, _, _),
i(_, _, _, _),
i(_, _, _, _)],
sadrzi(L, i(_, radosavljevic, _, _)),
sadrzi(L, i(_, _, kuglanje, _)),
sadrzi(L, i(nemanja, _, 'mini golf', _)),
sadrzi(L, i(_, _, bilijar, pica)),
sadrzi(L, i(milica, _, _, _)),
sadrzi(L, i(_, milic, _, _)),
sadrzi(L, i(_, _, 'stoni fudbal', _)),
sadrzi(L, i(marko, _, _, nacos)),
sadrzi(L, i(_, markovic, _, kokice)),
sadrzi(L, i(ivana, stefanovic, _, _)),
sadrzi(L, i(_, _, _, sladoled)),
not(sadrzi(L, i(nemanja, radosavljevic, _, _))),
not(sadrzi(L, i(_, radosavljevic, kuglanje, _))),
not(sadrzi(L, i(milica, milic, _, _))),
not(sadrzi(L, i(marko, _, 'stoni fudbal', _))),
not(sadrzi(L, i(milica, _, bilijar, _))).
