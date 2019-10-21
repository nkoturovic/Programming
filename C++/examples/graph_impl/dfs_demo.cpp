#include "graph.hpp"
#include "graph_algorithm.hpp"


int main()
{
    /***********************
     *      A(S)           *
     * B<--4-|----20->C(F) *
     * |     |        ^
     * |     |2       |
     * |     v        |
     * |-3-> D----5---|     *
     *                   *
    ************************/
    Graph<std::string, int, true> g;
    g.add_connection("a", "b", 4);
    g.add_connection("a", "c", 20);
    g.add_connection("a", "d", 2);
    g.add_connection("b", "d", 3);
    g.add_connection("d", "c", 5);

    std::vector<std::string> dfs_path = dfs<std::string, int>(g, "a", "c");

    std::string prev = "a";
    int distance = 0;
    for (const auto& s : dfs_path) {
        auto neigh = g.get_adj_list(prev, s);
        distance += *neigh.begin();
        prev = s;
        std::cout << " -> " << s;
    }
    std::cout << '\n';
    std::cout << "Distance: " << distance << '\n';


    return 0;
}
