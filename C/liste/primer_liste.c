#include <stdio.h>
#include "liste.h"

void print_int_func(void * a)
{
	if (a == NULL) {
		fprintf(stderr, "Indeks ne postoji\n");
		return;
	}

	printf("%d", *((int*) a));
}

int compare_int_func(void *a, void *b)
{
	if (a == NULL || b == NULL) {
		fprintf(stderr, "Poredjenje podatka na NULL pointer-u\n");
		return 1;
	}

	return *(int*)a - *(int*)b;
}

int main()
{
	
	_cvor *lista = NULL;	

	printf("Unesite broj elemenata liste: ");

	int n;
	scanf("%d", &n);
	int niz[n];

	while (n > 0) {
		scanf("%d", &niz[n]);
		dodaj_na_kraj(&lista, &niz[n]);
		n--;
	}

	ispisi_listu(lista, print_int_func);	
	int *ind3 = (int *) na_indeksu(lista, 3);

	if (ind3 != NULL)
		printf("Na indeksu 3: %d\n", *ind3 );

	if (ind3 != NULL)
		*ind3 = 777;

	ind3 = (int *) na_indeksu(lista, 3);

	if (ind3 != NULL)
		printf("Na indeksu 3: %d\n", *(int *) na_indeksu(lista, 3));

	ispisi_listu(lista, print_int_func);	
	printf("Velicina: %d\n", broj_elemenata(lista));
	printf("Prvi el: %d\n", *(int * ) na_indeksu(lista, 0));
	printf("Posl el: %d\n", *(int * ) na_indeksu(lista, broj_elemenata(lista)-1));

	int trazeni_podatak = 4;
	int * pr_podatak;
	pr_podatak = (int *) pronadji_podatak(lista, &trazeni_podatak, compare_int_func);
	if (pr_podatak != NULL) {
		printf("Podatak: %d, Indeks podatka: %d\n", 
			* pr_podatak,
			pronadji_indeks_podatka(lista, &trazeni_podatak, compare_int_func));
	} else {
		printf("Podatak nije pronadjen");
	}

	return 0;
}
