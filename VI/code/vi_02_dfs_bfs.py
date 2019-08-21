#!/usr/bin/env python3

from vi_01_graph import Graph

# TODO Vazno pitanje, da li ovi algoritmi daju put kao
# sve sto je bilo potrebno da se obidje pretragom ili se
# na osnovu toga pravi put gde se eliminisu nepotrebne grane ???
# pogledati mesto gde izbacujemo n sa steka u dfs kao u knjizi
# da nije tako mogli bismo jednostavno uzeti visited i vratiti
# nisu li ovo ustvari modifikacija algoritma dfs/bfs prilagodjene pretrazi

# DFS kao u knjizi
def dfs(graph, start, stop):
    path = [start]
    visited = {start}

    # dok god stek put nije prazan
    while len(path) > 0:
        # uzmi cvor n sa vrha steka put
        n = path[-1]

        # ako je n ciljni cvor
        if n == stop:
            return path # vrati put

        # izaberi prvog potomka koji nije u skupu posecenih cvorova (lazy)
        m = next((m for m,_ in graph.get_neighbors(n) if m not in visited), None)

        # ako n nema potomaka koji nisu poseceni
        if m == None:
            path.pop() # izbaci n sa steka
        # inace
        else:
            # izaberi prvog takvog potomka i dodaj ga na stek put
            # i u skup posecenih cvorova
            path.append(m)
            visited.add(m)

    return None


def dfs1(graph, start, stop):
    visited = []
    to_visit = [start]
    
    while len(to_visit) > 0:
        curr = to_visit.pop(0) # FO in LIFO
        visited.append(curr)

        if curr == stop:
            return visited
        
        for n, _ in graph.get_neighbors(curr):
            if n not in visited:
                # of 2 same leave LAST in
                if n in to_visit:
                    to_visit.remove(n) 
                to_visit.insert(0, n)

    return None # trazeni put ne postoji


from collections import deque

# BFS kao u knjizi
def bfs(graph, start, stop):
    # stavi samo polazni cvor u red S
    S = deque([start])
    visited = set([start])
    parent = {start : start}

    while len(S) > 0:
        # uzmi n sa pocetka reda S i obrisi ga iz reda
        n = S.popleft()

        # ako je n ciljni cvor
        if n == stop:
           # Izvesti o uspehu i vrati put od polaznog do ciljnog cvora
           # (iduci unazad od ciljnog cvora);
           path = [] 
           
           while parent[n] != n:
               path.append(n)
               n = parent[n]

           path.append(start)
           path.reverse()
           return path
        # za svaki od potomaka m cvora n
        for m,_ in graph.get_neighbors(n):
           # za koga nije definisan roditelj
           if m not in parent:
               # zapamti n kao roditelja
               parent[m] = n
               visited.add(m)

               # i dodaj ga na kraj reda S
               S.append(m)

    return None # trazeni put ne postoji


def bfs1(graph, start, stop):
    visited = []
    to_visit = [start]
    
    while len(to_visit) > 0:
        curr = to_visit.pop(-1) # FO in FIFO
        visited.append(curr)

        if curr == stop:
            return visited
        
        for n, _ in graph.get_neighbors(curr):
            if n not in visited:
                # of 2 same leave FIRST in
                if n not in to_visit:
                    to_visit.insert(0, n)

    return None



if __name__ == '__main__':
    graph = Graph({'1': [('2', 1), ('3', 1), ('4', 1), ('5', 1)],
                   '2': [('1', 1), ('3', 1)],
                   '3': [('1', 1), ('2', 1), ('4', 1), ('6', 1)],
                   '4': [('1', 1), ('3', 1), ('5', 1), ('6', 1)],
                   '5': [('1', 1), ('4', 1), ('6', 1)],
                   '6': [('3', 1), ('4', 1), ('5', 1)]})

    print('dfs:', dfs(graph, '1', '6'))
    print('bfs:', bfs(graph, '1', '6'))
    print('dfs1:', dfs1(graph, '1', '6'))
    print('bfs1:', bfs1(graph, '1', '6'))
