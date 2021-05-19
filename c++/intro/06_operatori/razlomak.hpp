#ifndef __RAZLOMAK_H__
#define __RAZLOMAK_H__
/* Donje crte ne moraju !!! */

#include <string>

class Razlomak {
// Prijatelj moze da pristupa privatnim clanovima klase
// Ne mora ako je sve public
// friend Razlomak operator+(const Razlomak &r1, const Razlomak &r2);
// std::ostream& operator<<(const std::ostream& out, const Razlomak &r);

public:
    int brojilac = 0;
    int imenilac = 1;

    Razlomak();
    Razlomak(int brojilac, int imenilac);

    // bool is_positive() { return true; } - Moglo je i ovde da se 
    // implementira, ali smo ispod jer cemo obicno razdvajati hpp i cpp
    static bool is_positive(Razlomak r);
    bool is_positive();

    // const reference - prosledjivanje argumenata (usteda performansi/memorije)
    static Razlomak zbir(const Razlomak &r1, const Razlomak &r2);

    std::string str() const;
};

Razlomak operator+(const Razlomak &r1, const Razlomak &r2);
std::ostream& operator<<(std::ostream& out, const Razlomak &r);

#endif
