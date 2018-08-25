#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

_cvor* napravi_cvor(void * podatak)
{
	_cvor* novi =  (_cvor *) malloc(sizeof(_cvor));
	if(novi == NULL) {
		fprintf(stderr, "Greska pri alokaciji memorije\n"); 
		exit(EXIT_FAILURE);
	}
  
	novi->podatak = podatak;
	novi->sledeci = NULL;
 
	return novi;
}

void dodaj_na_pocetak(_cvor** lista, void * podatak)
{
	_cvor* novi = napravi_cvor(podatak);    
	novi->sledeci = *lista;
	*lista = novi;
}

void ispisi_listu(_cvor* lista, void (*printel_func)(void*))
{
	printf("[");
	while (lista != NULL) {
		printel_func(lista->podatak);

		if (lista->sledeci)
			printf(", ");

		lista = lista->sledeci;
	}
	printf("]\n");
}

void dodaj_na_kraj(_cvor** lista, void * podatak)
{
	if(*lista == NULL) {
		_cvor* novi = napravi_cvor(podatak);
		*lista = novi;
		return;
	}
  
	dodaj_na_kraj(&(*lista)->sledeci, podatak);
}

void oslobodi_listu(_cvor* lista)
{
	if(lista) {
		oslobodi_listu(lista->sledeci);
		free(lista);
	}
}

void * na_indeksu(_cvor* lista, int indeks)
{
	if (lista == NULL)
		return NULL;

	if (indeks == 0) 
		return lista->podatak;
	
	return na_indeksu(lista->sledeci, --indeks);
}

int broj_elemenata(_cvor * lista) 
{
	int i = 0;
	_cvor * c = lista;
	while(c != NULL) {
	       	c = c->sledeci; 
		i++;
	}
	return i;	
}


void * pronadji_podatak(_cvor * lista, void * trazeni_podatak, int (*compare_func)(void* p1, void*p2))
{
	if (lista == NULL)
		return NULL;

	if (compare_func(trazeni_podatak, lista->podatak) == 0) {
		return lista->podatak;
	}
	return pronadji_podatak(lista->sledeci, trazeni_podatak, compare_func);
}


int pronadji_indeks_podatka(_cvor * lista, void * trazeni_podatak, int (*compare_func)(void* p1, void*p2))
{
	void * podatak_u_listi = pronadji_podatak(lista, trazeni_podatak, compare_func);

	if (podatak_u_listi == NULL)
		return -1;

	_cvor * c = lista;
	int index = 0;

	while (1) {
		if (c == NULL) 
			return -1;

		if (podatak_u_listi == c->podatak)
			return index;

		c = c->sledeci;
		index++;
	}
}
