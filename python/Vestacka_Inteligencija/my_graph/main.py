#!/usr/bin/env python3

from graph import Graph

# Not recomended
# adj = {'a': {'b':[1,2,3], 'c':[2,3,4]},
#  'b': {'d':[2]}
# }

g = Graph()
# g.add_connection('A', 'B', 3)
# g.add_connection('A', 'C', 2)
# g.add_connection('A', 'E', 4)
# g.add_connection('A', 'D', 6)
# g.add_connection('B', 'D', 5)
# g.add_connection('B', 'F', 5)
# g.add_connection('C', 'E', 1)
# g.add_connection('D', 'E', 2)
# g.add_connection('D', 'F', 1)
# g.add_connection('E', 'F', 4)

g.add_connection('Beograd', 'Budimpesta', 380)
g.add_connection('Beograd', 'Zagreb', 390)
g.add_connection('Beograd', 'Sarajevo', 290)
g.add_connection('Beograd', 'Podgorica', 450)
g.add_connection('Beograd', 'Skoplje', 430)
g.add_connection('Beograd', 'Bukurest', 590)
g.add_connection('Sofija', 'Skoplje', 240)
g.add_connection('Skoplje', 'Podgorica', 350)
g.add_connection('Podgorica', 'Sarajevo', 230)
g.add_connection('Sarajevo', 'Zagreb', 400)
g.add_connection('Zagreb', 'Budimpesta', 340)
g.add_connection('Budimpesta', 'Bukurest', 840)
g.add_connection('Bukurest', 'Sofija', 360)

# print(g.closest_neighbor('A'))
# print(g.adj_list)
# print(g.vertices())
# start, finish = input(), input()
print(g.dijkstra('Bukurest', 'Podgorica'))
