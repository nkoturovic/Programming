#!/usr/bin/env python3

import constraint

def sum_constr_func(x,y,z):
    if x + y + z == 15:
        return True

problem = constraint.Problem()
problem.addVariables("abcdefghi", range(1,10))

#    | a b c |
#    | d e f |
#    | g h i |

# Rows constraints
problem.addConstraint(sum_constr_func, "abc")
problem.addConstraint(sum_constr_func, "def")
problem.addConstraint(sum_constr_func, "ghi")
# Colunms constraints
problem.addConstraint(sum_constr_func, "adg")
problem.addConstraint(sum_constr_func, "beh")
problem.addConstraint(sum_constr_func, "cfi")
# Diagonals constraints
problem.addConstraint(sum_constr_func, "aei")
problem.addConstraint(sum_constr_func, "ceg")

solutions = problem.getSolutions()
for i, s in enumerate(solutions):
   print(str(i+1) + '--------\n') 
   print(\
    str('| {} {} {} |\n'
        '| {} {} {} |\n'
        '| {} {} {} |\n').format(s['a'], s['b'], s['c'],\
                   s['d'], s['e'], s['f'],\
                   s['g'], s['h'], s['i']))
