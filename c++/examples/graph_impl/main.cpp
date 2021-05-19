#include <iostream>
#include "graph.hpp"


int main()
{

	/* Could be anything */
	Graph<std::string, int, false> g;
	std::string separator("-----------------");

	std::string node1("Pera");
	std::string node2("Mika"); 
	std::string node3("Sreta"); 
	std::string node4("Laza"); 

	g.add_connection(node1, node2, 3);
	g.add_connection(node2, node1, 4);
	g.add_connection(node1, node4, 7);
	std::cout << g << separator << std::endl;

	Graph<std::string, int, true> g2;
	g2.add_connections("Mika", "Laza", {1, 2, 3, 6 ,8});
	std::cout << g2 << separator << std::endl;

	Graph<std::string, int> g3;
	g3.add_connections("Mika", "Laza", {1, 2, 3, 6 ,8});
	std::cout << g3 << separator << std::endl;


	Graph<std::string, int> g4({ 
			{ "Mika", { 
					{ "Laza", {1, 3, 4} }, 
					{ "Pera", {2, 2, 2} } 
				  } 
			},
			{ "Pera", {
					{ "Deja", {2, 3, 7} }
				  } 
			},
			{ "Deja", {
					{ "Mika", {3, 8, 22} }
				  } 
			}
			});

	std::cout << g4;

	return 0;
}
