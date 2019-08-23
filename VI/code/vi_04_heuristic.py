from vi_01_graph import Graph

# heuristic promenljiva je funkcija koja
# slika cvor grafa u broj (heuristicku procenu)
def greedy(graph, start, stop, heuristic):
    parent = { start : start }

    # tekuci cvor n postavi na polazni cvor
    n = start
    distance = 0

    # ponavljaj beskonacno
    while True:
        # ako se vratimo u vec posecen
        # cvor upali smo u besk. petlju
        if n != start and n in parent.values():
            return None, None
        
        # ako je n ciljni cvor
        if n == stop:
            # konstruisi put i vrati uspeh
            path = []
            while parent[n] != n:
                path.append(n)                
                n = parent[n]

            path.append(start)
            path.reverse()
            return path, distance 

        # ako nema direktno dostupnih cvorova
        n_neighbors = graph.get_neighbors(n)
        if len(n_neighbors) == 0:
            # izvesti u o neuspehu
            return None, None

        # od dostupnih cvorova izaberi cvor 
        # sa najboljom heuristickom. ocenom
        m = min(n_neighbors, key=lambda e: heuristic(e[0]))
        distance += m[1]
        parent[m[0]] = n
        n = m[0]

    return (None, None)


def best_first(graph, start, stop, heuristic):
    open_list = [start]
    closed_list = []
    distance = {k : float('inf') for k in graph.adj_list.keys()}
    distance[start] = 0
    parent = {start : start}

    while len(open_list) > 0:

        # iz otvorene liste uzmi cvor sa najboljom ocenom f(x)
        f = lambda x: heuristic(x) # f(x) je heuristicka procena udaljenosti
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
            if m not in closed_list and m not in open_list:
                # dodaj m u otv. listu i oznaci n kao roditelja
                open_list.append(m)
                parent[m] = n
                n_to_m = next(x[1] for x in graph.get_neighbors(n) if x[0] == m)
                distance[m] = distance[n] + n_to_m

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

    put, rastojanje = greedy(graph, '1', '6', heuristic)
    print('---- Greedy ----')
    print('Put:', put)
    print('Rastojanje:', rastojanje)

    put1, rastojanje1 = best_first(graph, '1', '6', heuristic)
    print('---- Best Fist ----')
    print('Put:', put1)
    print('Rastojanje:', rastojanje1)
