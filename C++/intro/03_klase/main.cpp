#include <iostream>


class Razlomak {
public:
    int brojilac = 0, imenilac = 1;

    // bool is_positive() { return true; } - Moglo je i ovde da se 
    // implementira, ali smo ispod jer cemo obicno razdvajati hpp i cpp
    bool is_positive();
};

bool Razlomak::is_positive() { return true; }

int main() 
{
    Razlomak r;
    r.brojilac = 2;
    r.imenilac = 1;

    std::cout << r.brojilac << " / " << r.imenilac << std::endl;
    
    return 0;
}
