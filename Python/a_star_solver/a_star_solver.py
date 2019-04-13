#!/usr/bin/env python3
from math import sqrt

class Graph:
    def __init__(self, adjacency_list, h_table):
        self.adjacency_list = adjacency_list
        self.h_table = h_table
        
    def __str__(self):
        return str(self.adjacency_list)
        
    def get_neighbors(self, v):
        return self.adjacency_list[v]
    
    # Heuristika
    def h(self, n):
        return h_table[n]

    # Pronalazenje najkraceg puta pomocu algoritma A*
    def astar(self, start, stop):

        # Zatvorena lista je inicijalno prazna, a otvorena lista sadrzi samo polazni cvor
        open_list = [start]
        closed_list = []

        # g sadrzi tekuce udaljenosti od polaznog cvora (start) do ostalih cvorova, ukoliko se cvor ne nalazi
        # u mapi, podrazumevana vrednost udaljenosti je beskonacno
        g = {}
        
        # Udaljenost polaznog cvora od samog sebe je 0
        g[start] = 0

        # Mapa parents cuva roditelje cvorova
        parents = {}
        parents[start] = start
        
        ###### Log poruke ######################
        #_______________________________________________________________
        #Tekuci | Stanje orvorene liste              | u zarvorenu listu
        #Cvor   | cvor(roditelj, g+h)                | se dodaje
        #_______________________________________________________________
        log = []
        log.append( ('Tekuci', 'Stanje otvorenje liste', 'U zatvorenu') )
        log.append( ('cvor', 'cvor(roditelj, g+h)', 'L se dodaje') )
        log.append( ('', str(start) + '(-, ' + '0+' + str(self.h(start)) + ')', '') )
        ########################################

        # Izvrsavaj dok god ima elemenata u otvorenoj listi
        while len(open_list) > 0:
            n = None
            
            for v in open_list:
                if n == None or g[v] + self.h(v) < g[n] +  self.h(n):
                    n = v;
            
                    
            if n == None:
                print('Trazeni put ne postoji')
                return None

            # Ako je n ciljni cvor, izvesti o uspehu i vrati resenje konstruisuci put
            # od polaznog do ciljnog cvora (iduci unazad — od ciljnog cvora).
            if n == stop:
                path = []

                # do-while petlja ne postoji u Python-u
                while parents[n] != n:
                    path.append(n)
                    n = parents[n]

                # Dodajemo polazni cvor
                path.append(start)
                path.reverse()
                
                
                ###### Log poruke ######################
                #_______________________________________________________________
                #Tekuci | Stanje orvorene liste              | u zarvorenu listu
                #Cvor   | cvor(roditelj, g+h)                | se dodaje
                #_______________________________________________________________
                ########################################
                n = stop
                open_list.remove(n)
                open_list.sort(key=lambda x: (g[x] + self.h(x), self.h(x)) )
                stanje = [str(cv) + '(' + str(parents[cv]) + ',' + str(g[cv]) + '+' + str(self.h(cv)) + ')' + ', &' for cv in open_list] 
                
                tekuci_cvor = str(n) + '(' + str(g[n] + self.h(n)) + ')' 
                stanje_otv_liste = '&'.join(stanje)
                stanje_otv_liste = stanje_otv_liste.replace('&', '')
                poz_posl_zarez = stanje_otv_liste.rfind(",") 
                stanje_otv_liste = stanje_otv_liste[:poz_posl_zarez]

                u_zatv_listu_se_dodaje = str(n) + '(' + str(parents[n]) + ')'
                log.append( (tekuci_cvor, stanje_otv_liste, '') )

                tek_cv_max = 0
                log_otv_max = 0
                zatv_max = 0
                for m in log:
                    if len(m[0]) > tek_cv_max:
                        tek_cv_max = len(m[0])

                    if len(m[1]) > log_otv_max:
                        log_otv_max = len(m[1])

                    if len(m[2]) > zatv_max:
                        zatv_max = len(m[2])


                print('|' + ('-' * (tek_cv_max+1) + '|' + ('-' * (log_otv_max+2)) + '|' + '-' * (zatv_max + 1)) + '|') 
                print('|{:{tek_prec}}|{:{otv_prec}}|{:{zatv_prec}}|'.format(log[0][0], log[0][1], log[0][2], tek_prec=tek_cv_max + 1, otv_prec=log_otv_max + 2, zatv_prec=zatv_max+1))
                print('|{:{tek_prec}}|{:{otv_prec}}|{:{zatv_prec}}|'.format(log[1][0], log[1][1], log[1][2], tek_prec=tek_cv_max + 1, otv_prec=log_otv_max + 2, zatv_prec=zatv_max+1))
                    
                for m in log[2:]:
                    print('|' + ('-' * (tek_cv_max+1) + '|' + ('-' * (log_otv_max+2)) + '|' + '-' * (zatv_max + 1)) + '|') 
                    print('|{:^{tek_prec}}|{:{otv_prec}}|{:^{zatv_prec}}|'.format(m[0], m[1], m[2], tek_prec=tek_cv_max + 1, otv_prec=log_otv_max + 2, zatv_prec=zatv_max+1))
                print('|' + ('-' * (tek_cv_max+1) + '|' + ('-' * (log_otv_max+2)) + '|' + '-' * (zatv_max+1)) + '|') 

                result = " -> ".join(path)                
                print('Pronadjen put: {}'.format(result))
                return path

            # Za svaki cvor m koji je direktno dostupan izn𝑛 uradi sledece:
            for (m, weight) in self.get_neighbors(n):

                # Ako m nije ni u otvorenoj ni u zatvorenoj listi, dodaj ga u otvorenu listu
                # i oznaci n kao njegovog roditelja.
                if m not in open_list and m not in closed_list:
                    open_list.append(m)
                    parents[m] = n
                    g[m] = g[n] + weight

                # Inace, proveri da li je put od polaznog cvora do cvora m preko
                # cvora n bolji (kraci ili jeftiniji) od postojeceg puta do m
                # (trenutna vrednost g(m)). Ako jeste, promeni informaciju o roditelju
                # cvora m na cvor n i azuriraj vrednosti g(m), a ako je
                # m bio u zatvorenoj listi, prebaci ga u otvorenu.
                else:
                    if g[m] > g[n] + weight:
                        g[m] = g[n] + weight
                        parents[m] = n

                        if m in closed_list:
                            closed_list.remove(m)
                            open_list.append(m)

            # Izbaci n iz otvorene liste i dodaj ga u zatvorenu listu
            open_list.remove(n)
            open_list.sort(key=lambda x: (g[x] + self.h(x), self.h(x)))
            
            closed_list.append(n)
            
            ###### Log poruke ######################
            #_______________________________________________________________
           #Tekuci | Stanje orvorene liste              | u zarvorenu listu
           #Cvor   | cvor(roditelj, g+h)                | se dodaje
            #_______________________________________________________________
            ########################################
            tekuci_cvor = str(n) + '(' + str(g[n] + self.h(n)) + ')'
            stanje = [str(cv) + '(' + str(parents[cv]) + ',' + str(g[cv]) + '+' + str(self.h(cv)) + ')' + ', &' for cv in open_list] 
            stanje_otv_liste = '&'.join(stanje)
            stanje_otv_liste = stanje_otv_liste.replace('&', '')
            poz_posl_zarez = stanje_otv_liste.rfind(",")
            stanje_otv_liste = stanje_otv_liste[:poz_posl_zarez]
            
            u_zatv_listu_se_dodaje = str(n) + '(' + (str(parents[n]) if parents[n] != n else '-') + ')'
            log.append( (tekuci_cvor, stanje_otv_liste, u_zatv_listu_se_dodaje) )

        #  Obavesti da trazeni put ne postoji (otvorena lista je prazna i uspeh nije prijavljen).
        print('Trazeni put ne postoji')
        return None


#######################################################
##################### PRIMERI #########################
#######################################################
print('Zadatak 1 (Vezbe)')
adjacency_list = {
    'A': [('B', 10), ('C', 1)],
    'B': [('D', 6), ('C', 8), ('A', 10), ('E', 4)],
    'C': [('D', 1), ('B', 8), ('A', 1)],
    'D': [('C', 1), ('B', 6), ('E', 1)],
    'E': [('B', 4), ('D', 1)]
}

h_table = {
    'A': 1,
    'B': 0,
    'C': 1,
    'D': 1,
    'E': 1
}

g = Graph(adjacency_list, h_table)
g.astar('A','B')

#######################################################
print()
print('Zadatak 4.3')
adjacency_list = {
    'A': [('B', 1), ('C', 2)],
    'B': [('A', 1), ('D', 3)],
    'C': [('A', 2), ('D', 1), ('A', 1)],
    'D': [('B', 3), ('C', 1)]
}

h_table = {
    'A': 2,
    'B': 1,
    'C': 1,
    'D': 0,
}
g = Graph(adjacency_list, h_table)
g.astar('A','D')

#######################################################
print()
print('Primer 3.5 (Iz knjige)')
adjacency_list = {
    'A': [('D', 6), ('G', 5)],
    'B': [('H', 2), ('F', 3), ('E', 2)],
    'C': [('D', 4)],
    'D': [('A', 6), ('C', 4), ('H', 3), ('F', 3)],
    'E': [('B', 2)],
    'F': [('B', 3), ('H', 5), ('D', 3)],
    'G': [('A', 5), ('H', 4)],
    'H': [('D', 3), ('F', 5), ('G', 4), ('B', 2)]
}

h_table = {
    'A': 6,
    'B': 1,
    'C': 6,
    'D': 5,
    'E': 0,
    'F': 3,
    'G': 6,
    'H': 3 # -> 4 postaje nekonzistentna
}

g = Graph(adjacency_list, h_table)
g.astar('A','E')

#######################################################
print()
print('Primer kolokvijuma 2017/2018')
print('1. a)')

adjacency_list = {
    'A': [('B', 20), ('C', 50), ('D', 100)],
    'B': [('C', 200), ('E', 110), ('A', 20)],
    'C': [('A', 50), ('B', 200), ('D', 30)],
    'D': [('A', 100), ('C', 30), ('E', 30)],
    'E': [('D', 30), ('B', 100)]
}

h_table = {
    'A': 105, 
    'B': 100,
    'C': 50, 
    'D': 20,
    'E': 0 
}
g = Graph(adjacency_list, h_table)
g.astar('A', 'E')

#######################################################
# Konvertuje lavirint u graf
######################################################
#### POMOCNA F-JA######
def char_range(c1, c2):
    """Generates the characters from `c1` to `c2`, inclusive."""
    for c in range(ord(c1), ord(c2)+1):
        yield chr(c)

def maze_to_graph(maze_matrix, h, dot_weight, hash_weight):
        adjacency_list = {}
        h_table = {}
        start = None
        finish = None
        
        n = len(maze_matrix)
        m = len(maze_matrix[0])
        
        for i in range(n):
            for j in range(m):
                chars = list(char_range('A', 'Z'))
                v = chars[i*m + j]
                neighbors = []
                
                if maze_matrix[i][j] != 'X':
                    
                    if maze_matrix[i][j] == 'S':
                        start = v
                    
                    if maze_matrix[i][j] == 'F':
                        finish = v
                    
                    if i > 0:
                        if maze_matrix[i - 1][j] != 'X':
                            w = (i-1, j)
                            if maze_matrix[i - 1][j] == '#':
                                weight = hash_weight 
                            else:
                                weight = dot_weight
                            neighbors.append((chars[w[0] * m + w[1]], weight))
                            
                    if i < n - 1:
                        if maze_matrix[i + 1][j] != 'X':
                            w = (i+1, j)
                            if maze_matrix[i + 1][j] == '#':
                                weight = hash_weight 
                            else:
                                weight = dot_weight
                            neighbors.append((chars[w[0] * m + w[1]], weight))
                            
                    if j > 0:
                        if maze_matrix[i][j - 1] != 'X':
                            w = (i, j-1)
                            if maze_matrix[i][j - 1] == '#':
                                weight = hash_weight
                            else:
                                weight = dot_weight
                            neighbors.append((chars[w[0] * m + w[1]], weight))
                            
                    if j < m - 1:
                        if maze_matrix[i][j + 1] != 'X':
                            w = (i, j+1)
                            if maze_matrix[i][j + 1] == '#':
                                weight = hash_weight 
                            else:
                                weight = dot_weight
                            neighbors.append((chars[w[0] * m + w[1]], weight))
                        
                adjacency_list[v] = neighbors

        list_of_chars = [c for c in char_range('A', 'Z')] 
        coords = {}

        for i in range(n):
            for j in range(m):
                coords[list_of_chars[i*m + j]] = (i, j)

        # Creating h_table
        for k, v in coords.items():
            curr_x = int(v[0])
            curr_y = int(v[1])
            fin_x = coords[finish][0]
            fin_y = coords[finish][1]
            curr = (curr_x, curr_y)
            fin = (fin_x, fin_y)
            h_table[k] = h(curr, fin)

        maze_scheme = list()
        for i in range(n):
                maze_scheme.append([list_of_chars[i*m + j] for j in range(m)])
                 
        return start, finish, adjacency_list, h_table, maze_scheme

def draw_maze_solution(maze_matrix, maze_scheme, solution):
    maze_solution = maze_matrix
    for i in range(len(maze_scheme)):
        for j in range(len(maze_scheme[0])):
                if (maze_scheme[i][j] in solution) and (maze_matrix[i][j] not in ['S', 'F']):
                    maze_solution[i][j] = '*'
    
    for row in maze_solution:
        for e in row:
            print(e, end=' ')
        print(end='\n')

    return maze_solution
    
    
# Funkcije koje se mogu koristiti kao heuristika
# u resavanju lavirinta
def menhetn(current, finish):
    curr_x, curr_y = current[0], current[1]
    finish_x, finish_y = finish[0], finish[1]
    return abs(curr_x - finish_x) + abs(curr_y - finish_y)

def euklid(current, finish):
    curr_x, curr_y = current[0], current[1]
    finish_x, finish_y = finish[0], finish[1]
    return round(sqrt((curr_x - finish_x)**2 + (curr_y - finish_y)**2), 1)

print()
print('Zadatak 4.8')
maze_matrix = [['#', 'F', '.', '.', '.'],
               ['.', 'X', '#', 'X', '.'],
               ['.', '.', 'S', '.', '.']]  

start, finish, adjacency_list, h_table, maze_scheme = maze_to_graph(maze_matrix, h=menhetn, dot_weight=1, hash_weight=6)
g = Graph(adjacency_list, h_table)

print('---- MAZE ----')
for row in maze_matrix:
        for e in row:
            print(e, end=' ')
        print()
print('--------------')
for row in maze_scheme:
        for e in row:
            print(e, end=' ')
        print()
print('--------------')
print('RESENJE:')
solution = g.astar(start, finish)
print('---- MAZE SOLUTION ----')
draw_maze_solution(maze_matrix, maze_scheme, solution)
print('--------------')
