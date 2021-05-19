#!/usr/bin/env python3

import json
import sys
from functools import reduce


# ime_dat = input("Unesi ume dat: ")
ime_dat = sys.argv[1]
nacionalnost = sys.argv[2]

try: 
    with open (ime_dat, "r") as f:
        fudbaleri = json.load(f)
except:
    print("Greska")

# lambda x: x+1

uporedi = lambda f1, f2: -1 if f1["Golovi"] < f2["Golovi"] else 1 if f1["Golovi"] > f2["Golovi"] else 0

fudb_nac = [f for f in fudbaleri if f["Nacionalnost"] == nacionalnost]

# sorted -> napravi novu sortiranu i .sort -> sortira bas tu listu
sortirani = sorted(fudb_nac, key=lambda f: f["Golovi"])

try: 
    with open ("rezultat.json", "w") as f:
        json.dump(sortirani, f, indent=2)
except:
    print("Greska pri upisu")

