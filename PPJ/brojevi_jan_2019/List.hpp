#ifndef _LIST_
#define _LIST_

#include <iostream>
#include <vector>

class List { 
private:
	std::vector <int> m_elementi;
	friend std::ostream& operator<<(std::ostream& out, const List& lista);
public:
	List() = default;
	List(std::vector <int> elementi);
	~List();

	void dodaj_na_kraj(int e);
	int operator[] (unsigned index); 
};

#endif
