#include <iostream>
#include "razlomak.hpp"

using namespace std; // Da ne pisemo non stop std:: ..

// Prosledjivanje po vrednosti (adresa je ta vrednost)
void swap1(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Prosledjivanje po referenci
void swap2(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    // Dinamicka alokacija
    int * a = new int;
    *a = 2;
    delete a; // free

    Razlomak * r = new Razlomak(1, 2);
    Razlomak * r1 = r;

    // Reference se ponašaju kao obične promenljive
    // a i dalje pokazuju na referentni objekat
    r1->imenilac = 5;

    Razlomak &ref_to_r = *r;
    ref_to_r.brojilac = 7;

    std::cout << "r: " << r->str() << std::endl; 
    std::cout << "r1: " << r1->str() << std::endl; 
    std::cout << "ref: " << ref_to_r.str() << std::endl; 

    swap2(ref_to_r.imenilac, ref_to_r.brojilac);
    std::cout << "r: " << r->str() << std::endl; 

     // delete r; // isto sto i
    // delete r1; // isto sto i
    delete &ref_to_r;

    // Alokacija i dealokacija 'C-ovskog' niza
    // malloc(32 * sizeof(int))  <=> 
    int * niz = new int[32];
    delete[] niz; // dealokacija niza
    
    return 0;
}
