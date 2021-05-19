#!/usr/bin/env python3

import constraint
from pprint import pprint

def equality_problem():
    problem = constraint.Problem()
    problem.addVariables(['alfa', 'beta'], [1,2,3,4])
    problem.addVariables('ij', [1,3])
    problem.addConstraint(lambda a, b, i, j: a+b == i+j, ['alfa', 'beta', 'i', 'j'])
    solutions = problem.getSolutions()
    return solutions


def main():
    pprint(equality_problem())

# execute only if run as a script ./, or with option
# python -m scriptname.py, but not when imported as module
if __name__ == "__main__":
    main()
