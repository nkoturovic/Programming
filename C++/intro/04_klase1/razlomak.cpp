#include "razlomak.hpp"

// Razlomak::Razlomak(int brojilac, int imenilac) {
//     this->brojilac = brojilac;
//     this->imenilac = imenilac;
// }

// Moze i na ovaj nacin (bolje)
Razlomak::Razlomak(int brojilac, int imenilac) : brojilac(brojilac), imenilac(imenilac) { }

bool Razlomak::is_positive(Razlomak r) {
    if (r.brojilac > 0)
        return true;
    else 
        return false;
}
bool Razlomak::is_positive() { return Razlomak::is_positive(*this); }
