#include "razlomak.hpp"

// Razlomak::Razlomak(int brojilac, int imenilac) {
//     this->brojilac = brojilac;
//     this->imenilac = imenilac;
// }
//
//
Razlomak::Razlomak() { }

// Moze i na ovaj nacin
Razlomak::Razlomak(int brojilac, int imenilac) : brojilac(brojilac), imenilac(imenilac) { }

bool Razlomak::is_positive(Razlomak r) {
    if (r.brojilac > 0)
        return true;
    else 
        return false;
}
bool Razlomak::is_positive() { return Razlomak::is_positive(*this); }

std::string Razlomak::str() const {
    return std::to_string(brojilac) + " / " + std::to_string(imenilac);
}

Razlomak Razlomak::zbir(const Razlomak &r1, const Razlomak &r2) {
    Razlomak zbir_r1_i_r2;
    zbir_r1_i_r2.imenilac = r1.brojilac * r2.imenilac + r2.brojilac * r1.imenilac;
    zbir_r1_i_r2.brojilac = r1.brojilac * r2.imenilac + r2.brojilac * r1.imenilac;
    return zbir_r1_i_r2;
}

Razlomak operator+(const Razlomak &r1, const Razlomak &r2) {
    return Razlomak::zbir(r1, r2);
}

std::ostream& operator<<(std::ostream& out, const Razlomak &r) {
    out << r.str();
    return out;
}
