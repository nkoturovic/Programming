#!/usr/bin/env python3

import sys
import os
import re

def make_origin_regex():
    reg_prefix = r"(?P<prefix>^([A-Za-z0-9]+)(?=_))"  # alfanum pre prvog _
    reg_name = r"(?P<name>[A-Za-z0-9_]+)"  # Alfanum + donja crta
    reg_ext = r"(?P<extension>\.(.+)$)"
    regex = reg_prefix + "_" + reg_name + reg_ext
    return re.compile(regex)

def make_target_regex(prefix, name, extension):
    reg_diff = r"(?P<diff>[A-za-z0-9_]+)" 
    regex = prefix + reg_diff + name + extension
    return re.compile(regex)

def main():
    origin_fnames = ["lib_sys_fajl.txt", "lib_nekifajl.txt", "nesto_dksjdkds_fkjfkfs.a"]
    target_fnames = ["lib_blah_sys_fajl.txt", "nesto_novo_dksjdkds_fkjfkfs.a", 
                   "lib_kdjs_djskjds23_fajl.txt", "lib_nesto_fajl.txt"]

    result = dict()
    origin_regex = make_origin_regex()

    for origin_fname in origin_fnames:
        m = origin_regex.search(origin_fname)
        if m != None:
            d = m.groupdict()
            target_regex = make_target_regex(d["prefix"], d["name"], d["extension"])

            for target_fname in target_fnames:
                m = target_regex.search(target_fname)
                if m != None:
                    result[origin_fname] = target_fname

    for (k, v) in result.items():
        print("{} -> {}".format(k, v))

if __name__ == "__main__":
    main()
