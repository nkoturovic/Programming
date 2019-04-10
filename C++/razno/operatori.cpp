#include <iostream>
#include <string>

/* Deklaracija ide u h ili hpp */
class Vozilo {
private:
	friend Vozilo operator + (const Vozilo &a, const Vozilo &b);
	friend std::ostream & operator << (std::ostream &out, const Vozilo &a);

	std::string boja;
public:
	int broj_vrata;
	// Metodi klasika
	std::string kako_sviras();
};

Vozilo operator + (const Vozilo &a, const Vozilo &b) {
	Vozilo c;
	c.broj_vrata = a.broj_vrata + b.broj_vrata;
	return c;
}

std::ostream& operator << (std::ostream &out, const Vozilo &a) {
	out << a.broj_vrata;
	return out;
}

/* Definicija bi trebalo u cpp, ali
 * ja je pisem ovde */
std::string Vozilo::kako_sviras() { return "Tin tin"; }

int main()
{

	Vozilo a, b;
	std::cout << (a + b).broj_vrata;
	std::cout << a + b << std::endl;

}
