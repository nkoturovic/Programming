#!/usr/bin/env python3 
# SHEBANG ^-^
import sys

# ---- FORMATIRANJE ----
a = b = 5
c, d = 1, 2 # Raspakivanje tupple-a
c, d = d, c # Swap u jednoj liniji 
# Formatiranje String-a kao u C-u
c_like_formated = '%d %06.4f %d' % (a, 2.22222, b)
print('Python je kul ' + c_like_formated)

# Formatiranje novo + datum
new_format = '{} {:06.2f} {}'.format(a, 2.22222, b)
print('Python je strava ' + new_format)

from datetime import datetime
new_format1 = '{prezime} {prezime}, {datum_rodjenja}' \
.format(
    ime='marko'.capitalize(),
    prezime='markovic'.capitalize(),
    datum_rodjenja=datetime(1995, 10, 3).strftime('%d.%m.%Y')
)
print(new_format1)

# ---- UNOS, EXCEPTIONS ---- 
try:
    unos = float(input('Unesite delilac: '))
    print(1/unos, end=' ura\n')
except ValueError as ex: # ValueError - bas za taj tip greske
    print('Niste uneli ceo broj: ' + str(ex), file=sys.stderr)
except ZeroDivisionError as ex:
    print('Upsss, delili ste 0: ' + str(ex), file=sys.stderr)

lista_namirnica = ['banane', 'secer', 'so', 'brasno', 'jabuke']

lista_namirnica.reverse() # obrce redosled
# ['jabuke', 'brasno' , so, secer, 'banane' ]

# ---- LISTE ----
lista_namirnica.sort() # ['banane', 'brasno', 'jabuke', 'secer', 'so'] 
lista_namirnica.append('ananas') # ['banane', ... ,'so', 'ananas']
lista_namirnica.extend(['mars', 'snickers']) # ['banane', ..., 'ananas', 'mars', 'snickers']
lista_namirnica.remove('mars') # ['banane', ..., 'ananas', 'snickers']
lista_namirnica.pop() # ['banane', 'brasno' ..., 'ananas']
lista_namirnica.pop(1) # ['banane', 'jabuke', ..., 'ananas']
lista_namirnica.insert(1, 'musli') # ['banane', 'musli, ... , 'ananas' ]
len(lista_namirnica) # Vraca duzinu liste
lista_namirnica.count('ananas') # 1
if 'ananas' in lista_namirnica: print('ananas je u listi')
lista_namirnica = sorted(lista_namirnica, reverse=False)
# Reverse ortiranje custom funkcijom
from functools import cmp_to_key as ctk
lista_namirnica = sorted(lista_namirnica, key=ctk(lambda e1,e2: 1 if e1 < e2 else -1))
lista_kasirki = ['Bilja', 'Sladja', 'Sloba']

# zip -> kreira iterabilni zip objekat
for k, n in zip(lista_kasirki, lista_namirnica):
    print(k, n);

# enumerate, kreira tuppleove oblika (rb, element)
for i, e in enumerate(lista_namirnica, 1):
    print(str(i) + ') ' + e)

# ---- STRINGOVI ----
s1, s2 = 'the quick brown fox', 'jumped over the lazy dog'
haystack, needle = s1 + ' ' + s2, 'lazy'
i = haystack.find(needle) # i = 36
is_found = 'found' if needle in haystack else 'not found'
str_lista = " ".join(lista_namirnica) # 'so secer musli banane ... ' 

# ---- ARGUMENTI KOMANDNE LINIJE ----
# lista argumenata je sys.argv
br_argumenata = len(sys.argv)
argumenti = sys.argv[1:]
print(argumenti)
# sys.exit("Kraj programa") -- Poruka o gresci -> sys.exit(0) - ok

# ---- (n)TORKE ----
n_0 = ()
n_1 = ('xD',) # bez zareza je obican broj
n_2 = ('xD', ':)')
n_3 = ('xD', ':)', ':D')
m_point = (1, 2)
m_point * 2 # (1, 2, 1, 2)
t_point = (3, 4)
m_plus_t_point = m_point + t_point # = (1, 2, 3, 4)

# ---- RECNIK (MAPA) ----
magacin = {
        'banana' : 100,
        'ananas' : 102,
        'brasno' : 98,
}
print(magacin['banana'])
L = list(magacin.items()) # <=> L = list(zip(magacin.keys(), magacin.values()))
print(L)
# zip to list
# back to dict
print(dict(L))
# unzip from list
L1, L2 = zip(*L)
print(L1, L2)

for (k,v) in magacin.items():
    print(k, v)

# ---- SKUPOVI ----
e = set() # Prazan skup
a = set([1,2,3,4,5,6])
b = {1, 2, 3, 4}
print('a presek b', a.intersection(b))
print('a unija b', a.union(b))
print('a razlika b', a.difference(b))
print('a disjunktno b', a.isdisjoint(b))
try:
    a.remove('8')
except KeyError as e:
    print('4 ne postoji u skupu', e)

a.discard('8') # isto kao remove ali bez Exception-a

def procitaj_datoteku(putanja):
    try:
        with open(putanja, 'r') as f:
            return f.read()
    except IOError as e:
        print('Greska pri otv: ', e, file=sys.stderr)
        sys.exit(1)

fcontent = procitaj_datoteku('podsetnik_python.py')

for i, linija in enumerate(fcontent.split('\n')):
    print(i, ' ', linija)


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
