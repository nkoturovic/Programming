#!/usr/bin/env python3
import random
from functools import reduce

# Traditional function with name
def add(a, b):
    return a + b

# Lambda is anonymous function, it's usually 
# one liner, return keyword is not needed
sum = lambda a, b: a + b
print(add(2,3), sum(2,3))

random_list = [(i, random.randint(1, 100)) for i in range(1,10)]
# Sorting in place by snd of (fst, snd)
random_list.sort(key=lambda t: t[1])

# example bellow: maps (a, b) -> (b, a)
# map fn returns iterator, we passed it to list constructor
swapped = list(map(lambda x: (x[1], x[0]), random_list))

# filter list - keep only (fst, snd) where fst + snd < 40
less_than_frty = list(filter(lambda x: x[0] + x[1] < 40, swapped))

# elwise sum: (a1, b1) + (a2, b2) -> (a1 + a2, b1 + b2)
# reduce does this on all elements from 1 .. length of iterable
elw_sum = reduce(lambda x, y: (x[0]+y[0], x[1]+y[1]), less_than_frty, (0,0))
print(elw_sum)
