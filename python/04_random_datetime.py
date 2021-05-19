#!/usr/bin/env python3
import random
from datetime import datetime

# Random number in (0,1)
print(random.random())
print(random.randint(1,100))   #   int in [1,100]
print(random.randrange(1,100)) #   int in [1,100)
print(random.randrange(1,100,2)) # int in [1,3, ... ,99]
# Random choice from list
myList = [2, 109, False, 10, "Lorem", 482, "Ipsum"]
random.choice(myList)

# Shuffling deck
deck = [card for card in range(1,53)]
random.shuffle(deck)
print(deck)

# Date and Time
dt = datetime.now()  # Current datetime
print(dt)
# Look at Linux man 2 strftime
print(dt.strftime("Date: %d.%m.%y")) 
print(dt.strftime("Time: %H:%M:%S"))
someday = datetime(2001, 4, 21, 13, 22)
print(someday)
