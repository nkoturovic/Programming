#include <iostream>
#include "razlomak.hpp"

using namespace std; // Da ne pisemo non stop std:: ..

int main()
{
    Razlomak r1(1, 2);
    Razlomak r2(3, 4);

    // Mogu da uradim ovo (GLUPO)
    Razlomak zbir_r1_i_r2;
    // zbir_r1_i_r2.imenilac = r1.brojilac * r2.imenilac + r2.brojilac * r1.imenilac;
    // zbir_r1_i_r2.brojilac = r1.brojilac * r2.imenilac + r2.brojilac * r1.imenilac;
    
    // Malo pametnije
    zbir_r1_i_r2 = Razlomak::zbir(r1, r2);
    std::cout << zbir_r1_i_r2.str() << std::endl;

    // CPP-ovski (skoro sve)
    std::cout << (r1 + r2).str() << std::endl;

    // Jos bolje, implementiran operator <<
    std::cout << r1 + r2 << std::endl;

    return 0;
}
