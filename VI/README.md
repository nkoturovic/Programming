---
title: VI - Beleške za praktični deo ispita
author: "[www.github.com/nkoturovic/Programming](www.github.com/nkoturovic/Programming)"
date: \today
---


\newpage


# Deo 1 - Pretraga
## Klasa Graph 

Graf je interno mapa koja predstavlja listu suseda, može se koristiti za predstavljanje i usmerenog i neusmerenog grafa. Kod neusmerenog grafa možemo primetiti da će se javiti "duple" informacije npr. A \rightarrow B i B \rightarrow A. Za sve naše potrebe ova implementacija će biti sasvim ok.

```{.python caption="Klasa Graph"}
class Graph:
    def __init__(self, adj_list):
        self.adj_list = adj_list

    def __str__(self):
        return str(self.adj_list)

    # Vraca listu suseda cvora v
    def get_neighbors(self, v):
        return self.adj_list[v]
```
Graf zadajemo na sledeći način
```{.python}
g = Graph({'A' : ['B', 'C'], 
            'B' : ['A'],
            'C' : ['A']})
print(g)
print(g.get_neighbors('A'))
```
\begin{verbatim}
{'A': ['B', 'C'], 'B': ['A'], 'C': ['A']}
['B', 'C']
\end{verbatim}

## DFS algoritam

DFS algoritam je vrsta algoritma za pretragu u kome se krećemo kroz graf ili stablo u dubinu pa se vraćamo na čvorove koje smo usput zaobišli. Naš algoritam neće vraćati čitav put koji smo prešli (nećemo uključiti sporedne grane tj. grane koje jesmo posetili, a koje ne vode ka cilju.)

```{.python caption="DFS - algoritam pretrage u dubinu"}
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

        # izaberi prvog potomka koji nije u skupu posecenih cvorova (lenjo uzima)
        m = next((m for m in graph.get_neighbors(n) if m not in visited), None)

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
```

## BFS Algoritam


Za razliku od DFS algoritma koji ide u dubinu, BFS algoritam prvo pretražuje sve susede pa onda ide nivo po nivo dublje. Kao i kod DFS algoritma, nećemo vraćati sve čvorove koje smo obišli, već samo put.

```{.python caption="BFS - algoritam pretrage u širinu"}
def bfs(graph, start, stop):
    # stavi samo polazni cvor u red S
    S = deque([start])
    visited = set([start])
    parent = {start : start}

    # dok red S nije prazan
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
        for m in graph.get_neighbors(n):
           # za koga nije definisan roditelj
           if m not in parent:
               # zapamti n kao roditelja
               parent[m] = n
               visited.add(m)
               # i dodaj ga na kraj reda S
               S.append(m)

    return None # trazeni put ne postoji
```

### BFS i DFS primer

Primenićemo BFS i DFS algoritam na primeru pretrage puta od čvora `1` do čvora `6`.

\begin{center}
\begin{tikzpicture}[scale=0.65,shorten >=1pt, auto, node distance=1cm,
   node_style/.style={circle,draw=black,fill=blue!20,font=\sffamily\large},
   edge_style/.style={draw=black,thick}]

    \node[node_style, fill=green!20] (v1) at (-3,2) {1};
    \node[node_style] (v2) at (-6,0) {2};
    \node[node_style] (v3) at (-3,-2) {3};
    \node[node_style] (v4) at (0,0) {4};
    \node[node_style] (v5) at (3,2) {5};
    \node[node_style, fill=red!20] (v6) at (3,-2) {6};
    \draw[edge_style]  (v2) edge (v1);
    \draw[edge_style]  (v3) edge (v1);
    \draw[edge_style]  (v4) edge (v1);
    \draw[edge_style]  (v1) edge (v5);
    \draw[edge_style]  (v3) edge (v2);
    \draw[edge_style]  (v4) edge (v3);
    \draw[edge_style]  (v6) edge (v3);
    \draw[edge_style]  (v4) edge (v5);
    \draw[edge_style]  (v4) edge (v6);
    \draw[edge_style]  (v5) edge (v6);
\end{tikzpicture}
\end{center}

```python
graph = Graph({'1': ['2', '3', '4','5'],
                 '2': ['1', '3'],
                 '3': ['1', '2', '4', '6'],
                 '4': ['1', '3', '5', '6'],
                 '5': ['1', '4', '6'],
                 '6': ['3', '4', '5']})

print('dfs:', dfs(graph, '1', '6'))
print('bfs:', bfs(graph, '1', '6'))
```

\begin{verbatim}
dfs: ['1', '2', '3', '4', '5', '6']
bfs: ['1', '3', '6']
\end{verbatim}

## Dijkstrin algoritam


```{.python caption="Dijkstrin algoritam"}
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
```

## Dijkstrin algoritam primer

Primenićemo Dijkstrin algoritam da nađemo najkraći put od čvora `1` do čvora `6` u sledećem grafu.

\begin{center}
\begin{tikzpicture}[scale=0.65,shorten >=1pt, auto, node distance=1cm,
   node_style/.style={circle,draw=black,fill=blue!20,font=\sffamily\large},
   edge_style/.style={draw=black,thick}]

    \node[node_style, fill=green!20] (v1) at (-3,2) {1};
    \node[node_style] (v2) at (-6,0) {2};
    \node[node_style] (v3) at (-3,-2) {3};
    \node[node_style] (v4) at (0,0) {4};
    \node[node_style] (v5) at (3,2) {5};
    \node[node_style, fill=red!20] (v6) at (3,-2) {6};
    \draw[edge_style]  (v2) edge[color=red, text=black, ultra thick] node{1} (v1);
    \draw[edge_style]  (v3) edge node{3} (v1);
    \draw[edge_style]  (v4) edge node{4} (v1);
    \draw[edge_style]  (v1) edge node{3} (v5);
    \draw[edge_style]  (v3) edge[color=red, text=black, ultra thick] node{1} (v2);
    \draw[edge_style]  (v4) edge[color=red, text=black, ultra thick] node{1} (v3);
    \draw[edge_style]  (v6) edge node{3} (v3);
    \draw[edge_style]  (v4) edge node{1} (v5);
    \draw[edge_style]  (v4) edge[color=red, text=black, ultra thick] node{1} (v6);
    \draw[edge_style]  (v5) edge node{2} (v6);
\end{tikzpicture}
\end{center}

```python
graph = Graph({'1': [('2', 1), ('3', 3), ('4', 4), ('5', 3)],
                 '2': [('1', 1), ('3', 1)],
                 '3': [('1', 3), ('2', 1), ('4', 1), ('6', 3)],
                 '4': [('1', 4), ('3', 1), ('5', 1), ('6', 1)],
                 '5': [('1', 3), ('4', 1), ('6', 2)],
                 '6': [('3', 3), ('4', 1), ('5', 2)]})

put, rastojanje = dijkstra(graph, '1', '6')
print('Put:', put)
print('Rastojanje:', rastojanje)
```
\begin{verbatim}
Put: ['1', '2', '3', '4', '6']
Rastojanje: 4
\end{verbatim}



## Podsetnik za algoritme

### DFS

Idem bez vraćanja do kraja, pamtim gde sam bio da ne idem opet.

**Pomoćne promenljive:** `[path]`, `{visited}`

Na kraj liste `[path]` smeštamo čvorove počevši od čvora `start`, u svakoj iteraciji uzimamo po jedan čvor n sa kraja ove liste, a potom dodajemo jednog njegovog potomka `m` koji nije u `{visited}` na kraj liste `[path]` i u skup `{visited}`. Ukoliko `n` nema potomka izbacujemo ga iz `[path]`. Rezultat ovoga je da ćemo ili doći do ciljnog čvora i tada stanje liste `[path]` predstavlja naš put ili će nam ponestati čvorova iz liste `[path]` što znači da put ne postoji.


### BFS

Idem pogledam sve susede, pa biram jednog da krenem tim putem

**Pomoćne promenljive:** red `[S]`, skup `{visited}`, mapa `{parent}`

U red `[S]` dodajem sve neposećene susede cvora `n` i markiram ih kao posećene, obeležim n kao njihovog roditelja. Dalje redom uzimam prvog sledećeg suseda i sve radim ispočetka dok ne naiđem na ciljni čvor ili dok ne nestane neposećenih čvorova. Put konstruišem na osnovu mape `{path}`


### Dijkstra

Rastojanje od početka do čvora koji ću sledeći izabrati je glavna vodilja, sledeći čvor je uvek onaj sused koji ima najmanje rastojanje od početnog čvora.

**Pomoćne promenljive:** skup neobr. čvorova `{Q}`, mapa `{distance}`, `{visited}`, `{parent}`

Svaki čvor koji uzmemo za tekući i obrišemo iz `{Q}` znači da smo do njega već našli najbliže rastojanje, tj. postao je tekući. Za svaki susedni koji je i u `Q` gledamo da li imamo bolje rešenje ako imamo, sređujemo roditelja i rastojanje. Dok nam ne nestane čvorova ili dođemo do ciljnog.
