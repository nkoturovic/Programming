#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>


template <typename VertexType, typename EdgeType, bool is_directed=false>
class Graph {
private:
	template <typename VT, typename ET, bool is_dir>
	friend std::ostream& operator<<(std::ostream& out, const Graph<VT, ET, is_dir>&graph);
	std::map<VertexType, std::map<VertexType, std::set<EdgeType>>> adj_list; 
public:
	Graph() = default;
	Graph(const std::map<VertexType, std::map<VertexType, std::set<EdgeType>>>&);

	void add_connection(const VertexType &v1, const VertexType &v2, const EdgeType&);
	void add_connections(const VertexType &v1, const VertexType &v2, const std::set<EdgeType>&);
	void add_connections(const std::map<VertexType, std::map<VertexType, std::set<EdgeType>>>&);
	void remove_connection(const VertexType&, const VertexType&, const EdgeType&);
	bool is_connected(const VertexType &v1, const VertexType &v2);
	std::map<VertexType, std::set<EdgeType>> get_adj_list(const VertexType &v);
	std::set<EdgeType> get_adj_list(const VertexType &v1, const VertexType &v2);
};


template <typename VertexType, typename EdgeType, bool is_directed=false>
std::ostream& operator<<(std::ostream& out, const Graph<VertexType, EdgeType, is_directed>&graph) {
	std::stringstream sstr;

	for (const auto &m : graph.adj_list) {
		sstr << m.first;
		if constexpr(is_directed) {
			sstr << " -> ";
		} else {
			sstr << " <-> ";
		}

		sstr << "\n";

		for (const auto& sm : m.second) {
			sstr << "     ";
			sstr << sm.first << ": ";
			for (const auto& set_el : sm.second) {
				sstr << set_el ;
				if (&set_el != &*std::prev(sm.second.end()))
					sstr << ", ";
			}
			sstr << "\n";
		}
	}
	out << sstr.str();
	return out;
}

template <typename VertexType, typename EdgeType, bool is_directed>
void Graph<VertexType, EdgeType, is_directed>::add_connection(const VertexType& v1, const VertexType& v2, const EdgeType& edge) {
	adj_list[v1][v2].insert(edge);

	if constexpr (!is_directed)
		adj_list[v2][v1].insert(edge);
	
}

template <typename VertexType, typename EdgeType, bool is_directed>
void Graph<VertexType, EdgeType, is_directed>::remove_connection(const VertexType& v1, const VertexType& v2, const EdgeType& edge) {
	adj_list[v1][v2].erase(edge);

	if constexpr (!is_directed)
		adj_list[v2][v1].erase(edge);

}


template <typename VertexType, typename EdgeType, bool is_directed>
bool Graph<VertexType, EdgeType, is_directed>::is_connected(const VertexType& v1, const VertexType& v2) {
	if (adj_list[v1][v2].empty()) {
		if constexpr(!is_directed) {
			if (!adj_list[v2][v1].empty())
				return true;
		}
		return false;
	}
	return true;
}



template <typename VertexType, typename EdgeType, bool is_directed>
Graph<VertexType, EdgeType, is_directed>::Graph(const std::map<VertexType, std::map<VertexType, std::set<EdgeType>>>& gmap) {
	add_connections(gmap);
}

template <typename VertexType, typename EdgeType, bool is_directed>
std::set<EdgeType> Graph<VertexType, EdgeType, is_directed>::get_adj_list(const VertexType& v1, const VertexType &v2) {
	return adj_list[v1][v2];
}

template <typename VertexType, typename EdgeType, bool is_directed>
std::map<VertexType, std::set<EdgeType>> Graph<VertexType, EdgeType, is_directed>::get_adj_list(const VertexType &v) {
	return adj_list[v];
}

template <typename VertexType, typename EdgeType, bool is_directed>
void Graph<VertexType, EdgeType, is_directed>::add_connections(const VertexType &v1, const VertexType &v2, const std::set<EdgeType>&edges) {
	for (auto &e : edges) add_connection(v1, v2, e);
}


template <typename VertexType, typename EdgeType, bool is_directed>
void Graph<VertexType, EdgeType, is_directed>::add_connections(const std::map<VertexType, std::map<VertexType, std::set<EdgeType>>>& gmap) {
	for (auto& m : gmap) {
		for (auto& sm : m.second) {
			adj_list[m.first].insert({sm.first, sm.second});
			if constexpr(!is_directed) {
				adj_list[sm.first].insert({m.first, sm.second});
			}
		}
	}
}
