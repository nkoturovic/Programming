#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdio.h>

/*******************************************
 * Podatak koji lista cuva moze biti       *
 * bilo sta na memorijskoj adresi          *
 * (void *) podatak, na toj adresi moze    *
 * biti podatak/podaci koji su             *
 * staticki/dinamicki alocirani            *
 *******************************************/
typedef struct _cvor
{
  void * podatak;
  struct _cvor* sledeci;
}_cvor;

_cvor* napravi_cvor(void * podatak);
void dodaj_na_pocetak(_cvor** lista, void * podatak);
void dodaj_na_kraj(_cvor** lista, void * podatak);
void oslobodi_listu(_cvor* lista);
int broj_elemenata(_cvor * lista);
void * na_indeksu(_cvor* lista, int indeks);
void ispisi_listu(_cvor* lista, void (*printel_func)(void *));
void * pronadji_podatak(_cvor * lista, void * trazeni_podatak, int (*compare_func)(void* p1, void*p2));
int pronadji_indeks_podatka(_cvor * lista, void * trazeni_podatak, int (*compare_func)(void* p1, void*p2));

#endif
