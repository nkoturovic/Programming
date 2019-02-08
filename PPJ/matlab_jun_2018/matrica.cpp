#include "matrica.hpp"


Matrica::Matrica(const std::vector<int> &prva_vrsta) {
	m_matrica.push_back(prva_vrsta);
}

void Matrica::dodaj_vrstu(const std::vector<int>& vrsta) {
    m_matrica.push_back(vrsta);
}

std::vector<int>& Matrica::operator[] (unsigned index) {
	return m_matrica[index];
}

const std::vector<int>& Matrica::operator[] (unsigned index) const {
	return m_matrica[index];
}

Matrica operator + (const Matrica &a, const Matrica &b) {
	Matrica rez;

	if (a.broj_vrsta() == b.broj_vrsta() && a.broj_kolona() == b.broj_kolona()) {
		rez.m_matrica.resize(a.broj_vrsta());
		for (unsigned i=0; i < a.broj_vrsta(); i++) {
			rez[i].resize(a.broj_kolona());
			for (unsigned j=0; j < a.broj_kolona(); j++) {
				rez[i][j] = a[i][j] + b[i][j];
			}
		}
	} else {
		std::cout << "Dimenzije se ne poklapaju" << std::endl;
	}

	return rez;
}

Matrica operator * (const Matrica &a, const Matrica &b) {
	Matrica rez;

	if (a.broj_vrsta() == b.broj_vrsta() && a.broj_kolona() == b.broj_kolona()) {
		rez.m_matrica.resize(a.broj_vrsta());
		for (unsigned i=0; i < a.broj_vrsta(); i++) {
			rez[i].resize(a.broj_kolona());
			for (unsigned j=0; j < a.broj_kolona(); j++) {
				rez[i][j] = a[i][j] * b[i][j];
			}
		}
	} else {
		std::cout << "Dimenzije se ne poklapaju" << std::endl;
	}

	return rez;
}

std::ostream& operator << (std::ostream &out, const Matrica &a) {

	out << '[';
	for (unsigned i=0; i < a.broj_vrsta(); i++) {
		out << '[';
		for (unsigned j=0; j < a.broj_kolona(); j++) {
			 out << a[i][j] ;
			if (j != a.broj_kolona()-1)
				out << ", ";
		}
		out << "]";
		if (i != a.broj_vrsta()-1) 
			out << ", ";
	
	}
	out << ']';

	return out;
}

unsigned Matrica::broj_vrsta() const {
	return m_matrica.size();
}

unsigned Matrica::broj_kolona() const {
	if (broj_vrsta() > 0) {
		return m_matrica[0].size();
	} else {
		return 0;
	}
}

Matrica Matrica::mul_matrix(const Matrica &a, const Matrica &b) {
	Matrica rez;
	if (a.broj_kolona() == b.broj_vrsta()) {
		rez.m_matrica.resize(a.broj_vrsta());
		for (unsigned i=0; i < a.broj_vrsta(); i++) {
			rez[i].resize(b.broj_kolona());
			for (unsigned j=0; j < b.broj_kolona(); j++) {
				for (unsigned k = 0; k < a.broj_kolona(); k++) {
					rez[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	} else {
		std::cout << "Dimenzije se ne poklapaju" << std::endl;
	}
	return rez;
}

Matrica Matrica::transponuj(const Matrica &a) {
	Matrica rez;

	rez.m_matrica.resize(a.broj_kolona());
	for (unsigned i=0; i < a.broj_kolona(); i++) {
		rez[i].resize(a.broj_vrsta());
		for (unsigned j=0; j < a.broj_vrsta(); j++) {
			rez[i][j] = a[j][i];
		}
	}
	return rez;
}
