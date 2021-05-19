#include <iostream>
#include "razlomak.hpp"

int main() 
{
    Razlomak r = Razlomak(1, 2);
    std::cout << r.brojilac << " / " << r.imenilac << std::endl;
    
    return 0;
}
