#include <iostream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

int main()
{

    adjacency_list<> g;
    adjacency_list<>::vertex_descriptor v1 = add_vertex(g);
    adjacency_list<>::vertex_descriptor v2 = add_vertex(g);
    adjacency_list<>::vertex_descriptor v3 = add_vertex(g);
    adjacency_list<>::vertex_descriptor v4 = add_vertex(g);


    typedef adjacency_list<>::edge_iterator iterator;

    add_edge(v1, v2, g);
    add_edge(v2, v3, g);
    add_edge(v4, v4, g);
    add_edge(v4, v1, g);
    std::pair<iterator, iterator> p = edges(g);

    for (auto it = p.first; it != p.second; ++it)
        std::cout << *it << " ";
    std::cout << '\n';

    //std::pair<adjacency_list<>::edge_descriptor, bool> p;


    return 0;
}
