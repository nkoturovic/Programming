#include <iostream>
#include <vector>
#include <map>

int main() 
{
    /* -===== VEKTOR =====- */
    std::vector<int> niz = {1, 2, 3, 4};
    niz.push_back(5); // dodavanje na kraj

    // Foreach petlja, moze i 
    //for (unsigned i=0; i < niz.size(); i++) std::cout << niz[i];
    for (int e : niz)
        std::cout << e << " ";
    std::cout << std::endl;

    std::cout << "Velicina niza: " << niz.size();

    /* -====== MAPA ======- */
    // Ime namirnice -> komada
    std::map<std::string, int> namirnice;
    namirnice["jaja"] = 3;
    namirnice["banane"] = 5;
    namirnice["mleko"] = 2;

    std::cout << namirnice["mleko"]; // 2

    // Ovo moze tek od cpp17, drugacije preko iteratora
    for (auto [k, v] : namirnice)
        std::cout << k << " -> " << v << std::endl;

}
