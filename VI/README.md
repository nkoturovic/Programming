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
