% domen X-a u ovom trenutku je [-intmax,intmax]
% mogli smo staviti X :: 1..10
kvadrati(Vars) :-  Vars :: 1..100,
                   X*X #= Vars,
                   labeling(Vars).


suma_razl_deset(X, Y, Z) :- X :: 1..9,
                            Y :: 1..9,
                            Z :: 1..9,
                            alldifferent([X, Y, Z]),
                            X + Y + Z #= 10,
                            labeling(X), labeling(Y), labeling(Z).
