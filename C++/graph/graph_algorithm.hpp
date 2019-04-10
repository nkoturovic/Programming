#include "graph.hpp"
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

template <typename VertexType, typename EdgeType, bool is_directed>
std::vector<VertexType> dfs(Graph<VertexType,EdgeType, is_directed> g, VertexType start, VertexType finish) {
   std::stack<VertexType, std::vector<VertexType>> path_stack;
   std::set<VertexType> visited;

    path_stack.push(start);
    while (!path_stack.empty()) {
       VertexType curr_node = path_stack.top();

       if (curr_node == finish) {

                std::vector<VertexType> retval;

               while (!path_stack.empty()) {
                   retval.push_back(path_stack.top());
                   path_stack.pop();
               }
               std::reverse(retval.begin(), retval.end());

               return retval;
       }

       std::map<VertexType, std::set<EdgeType>> neigh_map = g.get_adj_list(curr_node);

       std::set<VertexType> curr_neighbors;
       for (auto [k, _]: neigh_map) 
           curr_neighbors.insert(k);

       std::set<VertexType> unvisited_curr;

       std::set_difference(curr_neighbors.begin(), curr_neighbors.end(), visited.begin(), visited.end(), 
                       std::inserter(unvisited_curr, unvisited_curr.begin()));

       if (unvisited_curr.size() == 0) {
           path_stack.pop();
       } else {
           path_stack.push(*unvisited_curr.begin());
           visited.emplace(*unvisited_curr.begin());
       }
   }


             std::vector<VertexType> retval;

               while (!path_stack.empty()) {
                   retval.push_back(path_stack.top());
                   path_stack.pop();
               }

            std::reverse(retval.begin(), retval.end());
           return retval;
}
