#!/usr/bin/env python3
import os
import json

# print(os.listdir('./')) # list of dir contents 

# Vraca listu ['ime_foldera', [fajlovi], [direktorijumi] .. ]
for (curdir, dirs, files) in os.walk('./'):
    print('Exploring:', curdir)
    print('  Dirs:', dirs)
    print('  Files:', files)

rezultati = { 'Pera' : {'status' : 'polozio', 
                        'poeni'  : 10},
              'Zika' : {'status' : 'polozio', 
                        'poeni'  : 20},
              'Mika'   :   {'status' : 'Diskfalifikovan',
                            'poeni'  : '-'} 
}

try:
    with open('rezultati.json', 'w') as f:
        f.write(json.dumps(rezultati, indent=2))
except IOError:
    print('Neuspesno otvaranje datoteke za pisanje')

# Samo f ima lokalni doseg unutar with bloka,
# sadrzaj_map nastavlja da zivi
try:
    with open('rezultati.json', 'r') as f:
        sadrzaj_map = json.load(f)
except IOError:
    print('Neuspesno otvaranje datoteke za citanje')


for k,v in sadrzaj_map.items():
    print(k, v)
