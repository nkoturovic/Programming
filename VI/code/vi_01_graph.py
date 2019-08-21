#!/usr/bin/env python3

class Graph:
    def __init__(self, adj_list):
        self.adj_list = adj_list

    def __str__(self):
        return str(self.adj_list)

    # Vraca listu suseda cvora v
    def get_neighbors(self, v):
        return self.adj_list[v]

if __name__ == '__main__':
    g = Graph( {'A' : ['B', 'C'], 
                    'B' : ['A'],
                    'C' : ['A']} )
    print(g)
    print(g.get_neighbors('A'))
