#!/usr/bin/env python3

# Napisati Python skript koji iz datoteke ekstenzije .csv (npr. igraci.csv)
# cita statisticke podatke o ukupnom uspehu fudbalera. Putanja do datoteke
# se skriptu prosledjuje kao prvi argumenta komandne linije. Ukoliko prosledjena
# putanja do datoteke nema ekstenziju .csv, obavestiti korisnika i prekinuti rad skripta.

# Datoteka (.csv) koju parsiramo sadrzi sledece informacije:

# Ime i prezime igraca: Sastavljeno od najvise 3 reci od kojih je svaka zapisana slovima.
# Prva i poslednja obavezno pocinju velikim slovom, pracenim malim slovima, ostale mogu
# biti u tom obliku ili samo od malih slova.

# drzava - jedna rec. Prvo slovo je veliko, ostala su mala.

# broj golova - ceo broj > 0

# godina1-godina2 - godina1 oznacava pocetak karijere, a godina2 kraj karijere ukoliko
# je nastupao, inace nije navedena. Godina se pise sa 4 cifre.

# klubovi - Lista klubova u kojima je igrac igrao tokom karijere, razdvojeni karakterom,
# eventualno pratecim belinama. Ime kluba pocinje velikim slovom ali moze sadrzati i
# vise reci sastavljenih od slova i brojeva.

# *** Podaci su liniji su razdvojeni karakterom , i eventualnim belinama. Ukoliko neke
# linije ne zadovoljavaju navedenu specifikaciju, ne izdvajati ih

# *** Skriptu se prosledjuju i ostali argumenti i to ako se prosledi:
# -g  skript na standardni izlaz ispisuje opadajuci sortiran spisak
# igraca po broju datih golova po utakmici. Prikazuje se ime, prezime
# i broj datih golova po utakmici: broj# _ golova / broj_utakmica

# *** -t KLUB - skript izdvaja sve igrace koji su nekada igrali u klubu KLUB.
# Prikacije se ime, prezime i pocetak i duzina trajanja karijere.
# Ako kraj karijere nije poznat, oduzeti pocetak karijere od 2018. godine

# Primer pozivanja skripta: ./1.py rezultati.csv -g
# Primer pozivanja skripta: ./1.py rezultati.csv -t Manchester United

import sys
import os
import re

############ PROVERA ARGUMENATA ###############
br_arg = len(sys.argv) - 1

if (br_arg < 2):
    sys.exit('Morate proslediti bar 2 argumenta')

args = sys.argv[1:]

opcija = None
opc_klub = None

if br_arg == 2:
    if args[1] != '-g':
        sys.exit('Argumenti nisu dobri')
    else: opcija = 'g'

if br_arg >= 3:
    if args[1] != '-t':
        sys.exit('Argumenti nisu dobri')
    else:
        opcija = 't'
        opc_klub = " ".join(args[2:])

putanja_do_fajla = args[0]

if putanja_do_fajla.lower().endswith('.csv') is False:
    sys.exit('Morate proslediti csv fajl')

if os.path.exists(putanja_do_fajla) is False:
    sys.exit('Prosledjieni fajl ne postoji')

# opcija, opc_klub, args, br_arg, putanja_do_fajla
############ CITANJE FAJLA ##################
def procitaj_fajl(putanja):
    try:
        with open(putanja, 'r') as f:
            return f.read()
    except:
        sys.exit('Neuspesno otvaranje fajla')

sadrzaj_fajla = procitaj_fajl(putanja_do_fajla)
############ KREIRANJE REGEXA ###############
def napravi_regex_igraca():
    ime = r'(?P<ime>[A-Z][a-z]*\s*([A-Za-z][a-z]*)?\s*([A-Z][a-z]*)?)'
    drzava = r'(?P<drzava>[A-Z][a-z]+)'
    broj_golova = r'(?P<broj_golova>[1-9][0-9]*)'
    broj_utakmica = r'(?P<broj_utakmica>[1-9][0-9]*)'
    godina1 = r'\s*(?P<godina1>\d\d\d\d?)'
    godina2 = r'(?P<godina2>(\d\d\d\d){0,1}\s*)'
    klubovi = r'(?P<klubovi>.*)'
    z = r'\s*,\s*'
    regex = ime + z + drzava + z + broj_golova + z \
        + broj_utakmica + z + godina1 + '-' + godina2 + z \
        + klubovi
    return re.compile(regex)

regex_igraca = napravi_regex_igraca()
# POKUPI OVAKO ZA GREP I SED ZADATAK
# print(regex_igraca.pattern)

########### GLAVNI DEO PROGRAMA ############
lista_igraca = [] # lista igraca (igrac je (k,v) mapa)
# Stavimo igrace u listu
for m in regex_igraca.finditer(sadrzaj_fajla):
    igrac = m.groupdict()
    lista_igraca.append(igrac)

if opcija == 'g':
    for igrac in lista_igraca:
        igrac['gol_po_uta'] = float(igrac['broj_golova']) / float(igrac['broj_utakmica'])

    sortirani_igraci = sorted(lista_igraca, key=lambda e: e['gol_po_uta'], reverse=True)

    for igrac in sortirani_igraci:
        print('{:25}{:3.2f}'.format(igrac['ime'], igrac['gol_po_uta']))

elif opcija == 't':
    igrali_u_klubu = []
    for igrac in lista_igraca:
        klubovi_igraca = igrac['klubovi'].split(',')
        klubovi_igraca = [e.strip() for e in klubovi_igraca]

        if opc_klub in klubovi_igraca:
            igrali_u_klubu.append(igrac)

    for igrac in igrali_u_klubu:
        if igrac['godina2'].isnumeric():
            duzina_kar = int(igrac['godina2']) - int(igrac['godina1'])
        else:
            duzina_kar = 2018 - int(igrac['godina1'])

        print('{} {} {}'.format(igrac['ime'], igrac['godina1'], duzina_kar))
