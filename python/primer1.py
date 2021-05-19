#!/usr/bin/env python3

import sys
import os
import re

def napravi_regex_ulaz():
    reg_prefiks = r"(?P<prefiks>^([A-Za-z0-9]+)(?=_))"  # alfanum pre prvog _
    reg_naziv = r"(?P<naziv>[A-Za-z0-9_]+)"  # Alfanum + donja crta
    reg_ekstenzija = r"(?P<ekstenzija>\.(.+)$)"
    regex = reg_prefiks + "_" + reg_naziv + reg_ekstenzija
    return re.compile(regex)


def main():
    nazivi_fajlova1 = ["lib_sys_fajl.txt", "lib_nekifajl.txt", "nesto_dksjdkds_fkjfkfs.a"]
    nazivi_fajlova2 = ["lib_blah_sys_fajl.txt", "nesto_dksjdkds_fkjfkfs.a", "lib_kdjs_djskjds23_fajl.txt",
                       "lib_nesto_fajl.txt"]

    regex = napravi_regex_ulaz()
    target_regexes = []
    for naziv in nazivi_fajlova1:
        m = regex.search(naziv)
        if m != None:
            n = regex.groupdict();
            target_regexes.append(re.compile(n["prefiks"] + r"(?P<razlika>[A-za-z0-9_]+)" + n["naziv"] + n["ekstenzija"]))

    result = []
    for r in target_regexes:
        for n in nazivi_fajlova2:
            m = r.search(n)
            if m != None:
                result.append(n)

    print(result)


if __name__ == "__main__":
    main()
