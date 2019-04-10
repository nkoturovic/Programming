#include <iostream>

// using namespace std; // Nije neophodno
// std (namespace) - za Standardnu biblioteku template-a

/* U C++ postoje reference */
void swap(int* a, int *b)    
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bad_swap(int a, int b)
{
	int tmp = a;
	a = b;
	b = tmp;
}


/* U C++ postoje reference */
void ref_swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

class Auto {
public:
	int broj_vrata;
};

/* Prosledjivanje sa !!const Tip& je isto kao po vrednosti,
 * samo su bolje performanse jer ne mora dodatno da se kopira */
Auto zbir_vrata(const Auto &a, const Auto &b) {
	Auto c;
	c.broj_vrata = a.broj_vrata + b.broj_vrata;
	return c;
}

int main()
{
	// cout je objekat (Console Out) aa << je operator 
	// prosledjivanja na standardni izlaz.
	std::cout << "Zdravo svete" << std::endl;
	int a = 2, b = 3;
	int a_bad = 2, b_bad = 3;
	int a_ref = 2, b_ref = 3;

	std::cout << "Normal swap: ";
	swap(&a, &b);
	std::cout << "a: " << a << "b: " << b << std::endl;

	std::cout << "Bad swap: ";
	bad_swap(a_bad, b_bad);
	std::cout << "a: " << a_bad << "b: " << b_bad << std::endl;
	
	ref_swap(a_ref, b_ref);
	std::cout << "Ref swap: ";
	std::cout << "a: " << a_ref << "b: " << b_ref << std::endl;

	int &ref_to_a = a;
	ref_to_a = 5;
	std::cout << "a je sada: " << a << std::endl;

	return 0;
}
