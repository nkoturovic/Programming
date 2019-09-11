clan(X, [X|_]).
clan(X, [_|T]) :- clan(X, T).

% d(ime, prezime, vrsta, boja)
drugarice(X) :- X = [ 
d(_,_,_,_),
d(_,_,_,_),
d(_,_,_,_),
d(_,_,_,_)],
clan(d(milena,MilenaPrezime,sandale,MilenaBoja), X),
clan(d(kaca,andonov,KacaObuca,_), X),
clan(d(anja,AnjaPrezime,_,_), X),
clan(d(jelena,_,JelenaObuca,_), X),
clan(d(_,_,patike,_), X),
clan(d(_,bogdanovic,_,_), X),
clan(d(_,ranisavljevic,_,zelena), X),
clan(d(_,cugurovic,CugurovicObuca,_), X),
clan(d(_,_,cizme,braon), X),
clan(d(_,_,cipele,CipeleBoja), X),
clan(d(_,_,_,pink), X),
clan(d(_,_,_,crna), X),
KacaObuca \= cizme,
JelenaObuca \= patike,
AnjaPrezime \= bogdanovic,
MilenaBoja \= crna,
MilenaPrezime \= ranisavljevic,
CugurovicObuca \= cizme,
CipeleBoja \= pink.
