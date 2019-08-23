from vi_01_graph import Graph

def a_star(graph, start, stop, heuristic):
    open_list = [start]
    closed_list = []
    distance = {k : float('inf') for k in graph.adj_list.keys()}
    distance[start] = 0
    parent = {start : start}

    while len(open_list) > 0:

        # iz otvorene liste uzmi cvor sa najboljom ocenom f(x)
        # ocena f(x) je zbir udalj. od start i procene udalj. do finish
        f = lambda x: (distance[x] + heuristic(x), heuristic(x))
        # ako su distance[x] i heuristic(x) isti, gledamo heuristic, zato vracamo tuple
        open_list.sort(key=lambda x: f(x))

        n = open_list[0]

        # ako je n ciljni cvor
        if  n == stop:
            # konstrisi put i vrati ga kao rezultat
            path = []
            while parent[n] != n:
                path.append(n)
                n = parent[n]

            path.append(start)
            path.reverse()
            return path, distance[stop]

        # za svaki m dir. dostupan iz n 
        for m, weight in graph.get_neighbors(n):
            # ako m nije ni u otv. ni u zatv listi
            n_to_m = next(x[1] for x in graph.get_neighbors(n) if x[0] == m)
            if m not in closed_list and m not in open_list:
                # dodaj m u otv. listu i oznaci n kao roditelja
                open_list.append(m)
                parent[m] = n
                distance[m] = distance[n] + n_to_m
            # inace ako je novi put bolji od starog
            elif distance[n] + n_to_m < distance[m]:
                # postavi novi put za aktuelnu vrednost
                distance[m] = distance[n] + n_to_m
                parent[m] = n

        # izbaci n iz otvorene liste i dodaj ga u zatvorenu
        n = open_list.pop(0)
        closed_list.append(n)

    return None, None

if __name__ == '__main__':

    graph = Graph({'1': [('2', 1), ('3', 3), ('4', 4), ('5', 3)],
                   '2': [('1', 1), ('3', 1)],
                   '3': [('1', 3), ('2', 1), ('4', 1)],
                   '4': [('1', 4), ('3', 1), ('5', 1), ('6', 1)],
                   '5': [('1', 3), ('4', 1), ('6', 2)],
                   '6': [('4', 1), ('5', 2)]})

    # heuristika
    h = {'1' : 2,
         '2' : 2,
         '3' : 1,
         '4' : 1,
         '5' : 1,
         '6' : 0 }

    heuristic = lambda e: h[e]

    put, rastojanje = a_star(graph, '1', '6', heuristic)
    print('---- A star ----')
    print('Put:', put)
    print('Rastojanje:', rastojanje)
