#!/usr/bin/env python3
import constraint

def constraint_func(x,y,z):
    if x*y < z:
        return True
    else:
        return False

problem = constraint.Problem() # Making Problem
problem.addVariable('x', range(1, 10)) # Adding variable x
problem.addVariable('y', [n**2 for n in range(1,10)]) # Adding variable y
problem.addVariable('z', [1, 5, 7, 9]) # Adding variable z

# Adding constraint (constraint_func, variables order)
problem.addConstraint(constraint_func, ['x', 'y', 'z'])

possible_solution = problem.getSolution() # one solution
all_solutions = problem.getSolutions() # all solutions

print('One solution:', possible_solution)
print('All solutins:')

for solution in all_solutions:
    print('x:', solution['x'], 'y:', solution['y'], 'z:', solution['z'])
