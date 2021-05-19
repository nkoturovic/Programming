#!/usr/bin/env python3

import sys, os, datetime

######## Variable num of ARGS #########
''' 
*args and **kwargs allow you to pass a variable number of arguments to a function
*args - non keyworded arguments 
**kwargs - keyworded arguments  
'''

def myprint(*unnamed_args, **named_args):
    for v in unnamed_args:
        print(v)
    for k, v in named_args.items():
        print(k, '=', v)

myprint('why', 123, a = 1, b = 'fox')

#######################################
########### DECORATORS ################
def fst(ob):
    print('visited fst decorator')
    return ob

def snd(ob):
    print('visited snd decorator')
    return ob

@snd
@fst
def myfunc():
    print('my function')

myfunc()
''' output is:
visited fst decorator
visited snd decorator
'''

#######################################
########## ANOTHER EXAMPLE ############
def star(func):
    def inner(*args, **kwargs):
        print("*" * 30)
        func(*args, **kwargs)
        print("*" * 30)
    return inner

def percent(func):
    def inner(*args, **kwargs):
        print("%" * 30)
        func(*args, **kwargs)
        print("%" * 30)
    return inner

@star
@percent
def printer(msg):
    print(msg)

printer("Hello")
'''output is:
******************************
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Hello
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
******************************
'''
