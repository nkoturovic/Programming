#include "List.hpp"

std::ostream& operator<<(std::ostream& out, const List& lista) {
	out << "[ ";
	for (auto i = lista.m_elementi.cbegin(); i != lista.m_elementi.cend() - 1; i++) { 
		out << *i << ", "; 
	}
	out << *(lista.m_elementi.cend() - 1) << " ]"; 
	return out;
}

int List::operator[] (unsigned index) {
	if (index > m_elementi.size()) {
		std::cerr << "Index veci od velicine liste";
		return m_elementi[0];
	}
	return m_elementi[index]; 
}

void List::dodaj_na_kraj(int e) {
	m_elementi.push_back(e);
}
