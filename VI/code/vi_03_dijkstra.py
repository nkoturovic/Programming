from vi_01_graph import Graph

def dijkstra(graph, start, stop):
    # stavi sve cvorove grafa u skup Q
    Q = {k for k,_ in graph.adj_list.items()}

    # inicijalno rastojanja su beskonacno
    distance = {k : float('inf') for k in Q}
    distance[start] = 0 # za pocetni cvor 0
    parent = {start : start}

    # dok god skup Q nije prazan radi
    while len(Q) > 0:
        # izaberi iz Q cvor n koji je najblizi 
        # polaznom cvoru i obrisi ga iz Q
        n = min(Q, key=lambda e: distance[e])
        # ako je najmanje rastojanje inf, put
        # ne postoji, ovo je dodatni check
        if distance[n] == float('inf'):
            print('Trazeni put ne postoji')
            return None, None

        Q.remove(n)

        # ako je n ciljni cvor
        if n == stop:
            # konstruisi put od polaznog do ciljnog
            path = []
            while parent[n] != n:
                path.append(n)
                n = parent[n]

            path.append(start)
            path.reverse()
            return path, distance[stop]
        
        # za svaki cvor m iz Q koji je direktno dostupan iz n
        neighbors_in_Q = [(k,v) for k,v in graph.get_neighbors(n) if k in Q]
        for m,dist in neighbors_in_Q:
            # ako je tekuce rastojanje od start do m vece od start preko n do m
            if distance[m] > distance[n] + dist:
                # promeni info o roditelju cvora m i upamti novo tekuce rast.
                distance[m] = distance[n] + dist
                parent[m] = n

    return None, None


if __name__ == '__main__':
    graph = Graph({'1': [('2', 1), ('3', 3), ('4', 4), ('5', 3)],
                   '2': [('1', 1), ('3', 1)],
                   '3': [('1', 3), ('2', 1), ('4', 1), ('6', 3)],
                   '4': [('1', 4), ('3', 1), ('5', 1), ('6', 1)],
                   '5': [('1', 3), ('4', 1), ('6', 2)],
                   '6': [('3', 3), ('4', 1), ('5', 2)]})

    put, rastojanje = dijkstra(graph, '1', '6')
    print('Put:', put)
    print('Rastojanje:', rastojanje)
