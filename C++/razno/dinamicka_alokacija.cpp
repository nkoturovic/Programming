#include <iostream>

int main()
{
	/* Idejno vazi isto sve kao i u C-u za malloc i free i jos novih stvari */
	int * a = new int; // Dinamicki alocirana promenljiva tipa int
	delete a; // isto kao free

	int * niz = new int[20];

	for (int i = 0; i < 20; i++) {
		niz[i] = i;
	}

	for (int i = 0; i < 20; i++) {
		std::cout << niz[i] << " ";
	}
	std::cout << std::endl;

	delete a;
	delete[] niz;

	return 0;
}
