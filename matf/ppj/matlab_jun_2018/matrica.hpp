#ifndef _MATRICA_H_
#define _MATRICA_H_

#include <iostream>
#include <vector>


class Matrica {
private:
	std::vector<std::vector<int>> m_matrica;

	friend Matrica operator + (const Matrica &a, const Matrica &b);
	friend Matrica operator * (const Matrica &a, const Matrica &b);
	friend std::ostream& operator << (std::ostream &out, const Matrica &a);
public:
	void dodaj_vrstu(const std::vector<int>& vrsta);
	Matrica(const std::vector<int>& vrsta);
	Matrica() = default;
	unsigned broj_vrsta() const; 
	unsigned broj_kolona() const; 
	std::vector<int>& operator[] (unsigned index);
	const std::vector<int>& operator[] (unsigned index) const;

	static Matrica mul_matrix(const Matrica &a, const Matrica &b);
	static Matrica transponuj(const Matrica &a);

};

Matrica operator + (const Matrica &a, const Matrica &b);         
Matrica operator * (const Matrica &a, const Matrica &b);         
std::ostream& operator << (std::ostream &out, const Matrica &a); 


#endif
