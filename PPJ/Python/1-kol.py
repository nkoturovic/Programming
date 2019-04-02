#!/usr/bin/env python3

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

if br_arg == 3:
    if args[1] != '-t':
        sys.exit('Argumenti nisu dobri')
    else:
        opcija = 't'
        opc_klub = args[2]

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
        igrac = {}
        igrac['ime'] = m.group('ime')
        igrac['drzava'] = m.group('drzava')
        igrac['broj_golova'] = m.group('broj_golova')
        igrac['broj_utakmica'] = m.group('broj_utakmica')
        igrac['godina1'] = m.group('godina1')
        igrac['godina2'] = m.group('godina2')
        igrac['klubovi'] = m.group('klubovi')
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
