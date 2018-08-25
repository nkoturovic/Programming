PROGRAM=primer_liste
CFLAGS=-Wall -Wextra

$(PROGRAM): primer_liste.o liste.o
	gcc $^ $(CFLAGS) -o $@

primer_liste.o: primer_liste.c
	gcc $< $(CFLAGS) -c

liste.o: liste.c
	gcc $< $(CFLAGS) -c

.PHONY: 
	clean

clean: 
	rm -rf $(PROGRAM) *.o
