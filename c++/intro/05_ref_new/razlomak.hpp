#ifndef __RAZLOMAK_H__
#define __RAZLOMAK_H__
/* Donje crte ne moraju !!! */

#include <string>

class Razlomak {
public:
    int brojilac = 0;
    int imenilac = 1;

    Razlomak(int brojilac, int imenilac);

    // bool is_positive() { return true; } - Moglo je i ovde da se 
    // implementira, ali smo ispod jer cemo obicno razdvajati hpp i cpp
    static bool is_positive(Razlomak r);
    bool is_positive();

    std::string str();
};

#endif
