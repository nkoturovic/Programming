GOAL = main
CC = g++
FLAGS = -Wall -Wextra

$(GOAL): main.o funkcije.o
	$(CC) $^ -o $@

main.o: main.c funkcije.h
	$(CC) $< -c

funkcije.o: funkcije.c funkcije.h
	$(CC) $< -c

.PHONY:
	clean

clean: 
	rm *.o main 
