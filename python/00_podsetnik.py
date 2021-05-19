#!/usr/bin/env python3 - shebang
import os
from sys import exit as ex

# Pomoc: help(bilo_sta) ili pydoc(bilo_sta)

a, b = 1, 2 # a = 1, b = 2
a, b = b, a # swap

# ------- FORMATIRANJE ---------
c_like_formated = '%d %06.4f %d' % (a, 2.22222, b)
new_format = '{} {:06.2f} {}'.format(a, 2.22222, b)

new_format1 = '{prezime} {ime}' \
.format(
    ime='marko'.capitalize(),
    prezime='markovic'.capitalize(),
)

try:
    unos = float(input('Unesite delilac: '))
    print(1/unos, end=' ura\n')
except ValueError as ex: # ValueError - bas za taj tip greske
    print('Niste uneli ceo broj: ' + str(ex))
except ZeroDivisionError as ex:
    print('Upsss, delili ste 0: ' + str(ex))

# ------- Liste -------
L.append(e)             L.pop()        
L.extend([e1, e2])      L.pop(1)       
L.remove(e)             L.insert(1, e) 
L.count()               len(L)
min(L)                  max(L)


if e in L: print('e je u listi')
sorted(L, key=func)

# zip -> kreira iterabilni zip objekat
for e1, e2 in zip(L1, L2):
    print(e1, e2);

# enumerate, kreira tuppleove oblika (rb, element)
for i, e in enumerate(L, 1):
    print(str(i) + ') ' + e)


# --------- STRINGOVI ------------
s1, s2 = 'the quick brown fox', 'jumped over the lazy dog'
haystack, needle = s1 + ' ' + s2, 'lazy'
i = haystack.find(needle) # i = 36
is_found = 'found' if needle in haystack else 'not found'
str_lista = " ".join(L)

# ---- ARGUMENTI KOMANDNE LINIJE ----
# lista argumenata je sys.argv
br_argumenata = len(sys.argv)
argumenti = sys.argv[1:]
print(argumenti)
sys.exit("Kraj programa") # Poruka o gresci -> sys.exit(0) - ok

# ---- (n)TORKE ----
n_0 = ()              # Operacije 
n_1 = (1,)            n_2 + n_2 = (1, 2, 1, 2)   
n_2 = (1, 2)          n_2 * 2 = (1, 2, 1, 2)     

# ---- RECNIK (MAPA) ----
magacin = {
        'banana' : 100,
        'ananas' : 102,
        'brasno' : 98,
}
print(magacin['banana'])
L = list(magacin.items()) # <=> L = list(zip(magacin.keys(), magacin.values()))
dict(L)
L1, L2 = zip(*L)
 
dict.get(key, default=None)     dict.has_key(key)   
dict.clear()                    dict.update(dict2)  
dict.copy()                     dict.values()       

# ---- FAJLOVI ----
def procitaj_datoteku(putanja):
    try:
        with open(putanja, 'r') as f:
            return f.read()
    except IOError as e:
        print('Greska pri otv: ', e, file=sys.stderr)
        sys.exit(1)

def upisi_u_datoteku(putanja, sadrzaj):
    try:
        with open(putanja, 'w') as f:
            f.write(sadrzaj)
    except Exception as e:
        print('Greska pri upisi i dat:', e)

tekst = \
"""Ovo ce biti upisano u datoteku
bla bla bla
Python je strava bla bla bla"""

upisi_u_datoteku('izlaz.txt', tekst)

# Modovi za otvaranje datoteke slicno kao u C-u
# 'r' -> read 'w' -> write 'x' -> append

# ---- POMOC import io, help(io) ili pydoc io

# Main function (Python as a script) ./script.py
def main():
    print('Hello world')

# execute only if run as a script ./, or with option
# python -m scriptname.py, but not when imported as module
if __name__ == "__main__":
    main()
