#include <iostream>

/* Ukljucivanje zaglavlja */
#include <vector>
#include <map>
#include <array>
#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

int main()
{
	/* Videcemo vektor, mapu, array ... Pogledaj listu */

	/* Slicno kao niz[5] - fiksne duzine */
	std::array<int, 5> niz;

	/* Kod containter tipova, nije klasizan niz[] */

	for (int e : niz) 
		std::cout << e;
	std::cout << std::endl;

	for (auto e : niz) 
		std::cout << e;
	std::cout << std::endl;

	/* ima operator [] */
	std::cout << niz[0] << std::endl;

	/* VEKTOR */
	std::vector<std::string> stringovi;
	stringovi.push_back("Tamara"); // dodavanje na kraj
	std::cout << stringovi[0] << std::endl;

	/* Iteratori su pokazivaci (koji imaju jos neke povoljnosti) */
	/* Oni obicno referisu na element u nizu itd ... */

	/* auto */
	for (auto i = stringovi.begin(); i != stringovi.end(); i++) {
		std::cout << *i;
	}
	stringovi.insert(stringovi.begin(), "Tamara"); // dodavanje na pocetak
	
	std::map<std::string, float> namirnice;
	namirnice["Banana"] = 4;
	namirnice["Ananas"] = 1;

	auto pokazivac_iterator = namirnice.find("Ananas");
	if (pokazivac_iterator != namirnice.end()) {
		std::cout << "Pronadjen";
	} else {
		std::cout << "Nije pronadjen";

	}

	std::cout << std::endl;

	std::set<std::pair<int, float>> skup;
	skup.insert({5,2.222});
	skup.insert({5,2.222});
	skup.insert({1,3.141592});

	std::vector<std::pair<int, float>> vec;
	std::copy(skup.begin(), skup.end(), std::back_inserter(vec));

	for (auto i = vec.cbegin(); i != vec.cend(); i++) {
		std::cout << "(" << i->first << ", " << i->second << ")";
		if (i != vec.cend() - 1)
			std::cout << ", ";
	}
	std::cout << std::endl;


	std::vector<int> intovi{1,2,3,4,5,6,7,8,9,10};
	auto max_el_it = std::max_element(intovi.begin(), intovi.end());
	int sum = std::accumulate(intovi.begin(), intovi.end(), 0);
	std::cout << "Max: " << *max_el_it << std::endl; 
	std::cout << "Sum: " << sum << std::endl; 


	std::ostream_iterator<int> out_it (std::cout, ", ");
	std::copy(intovi.begin(), intovi.end(), out_it);

	std::string str1 = "Hello there";
	std::string str2 = "yes me";

	std::string &&str_middle = str1+ str2;
	std::cout << str_middle << std::endl;
	str1 = "new string";
	std::cout << str_middle << std::endl;
	// std::string novi(str_middle);
	// std::string novi = std::move(str_middle);
	std::string novi = std::move(str_middle);
	std::cout << str_middle << std::endl;
	std::cout << novi << std::endl;

	auto elementi_print = [](std::string a, int b) -> std::string { return std::move(a) + ", " + std::to_string(b); };
	std::string ispis = std::accumulate(intovi.begin() + 1, intovi.end(), std::to_string(intovi[0]), elementi_print);
	std::cout << ispis << std::endl;

		
	return 0;
}
