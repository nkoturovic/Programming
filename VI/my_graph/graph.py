class Graph:
    def __init__(self, adj_list=dict(), is_directed=False):
       self.adj_list = adj_list
       self.is_directed = is_directed

    def add_connection(self, v1, v2, distance):
        try:
            self.adj_list[v1][v2].append(distance)
        except KeyError:
            try:
                self.adj_list[v1]
            except KeyError:
                self.adj_list[v1] = dict() 

            self.adj_list[v1][v2] = list()
            self.adj_list[v1][v2].append(distance)
        if not self.is_directed:
            try:
                self.adj_list[v2][v1].append(distance)
            except KeyError:
                try:
                    self.adj_list[v2]
                except KeyError:
                    self.adj_list[v2] = dict() 

                self.adj_list[v2][v1] = list()
                self.adj_list[v2][v1].append(distance)

    def add_connections(self, v1, v2, distances):
        for distance in distances:
            self.add_connection(v1, v2, distance)

    def neighbors(self, v):
        neighbors = list(self.adj_list[v].keys())
        return neighbors

    def edges(self, v1, v2):
        v1,v2 = min(v1,v2), max(v1,v2)
        return self.adj_list[v1][v2]

    def closest_neighbor(self, v):
        neighbors = self.neighbors(v)
        closest_neigh = None
        closest_dist = float('Inf')
        for n in neighbors:
            for distance in self.adj_list[v][n]:
                if distance < closest_dist:
                    closest_dist = distance
                    closest_neigh = n
        return closest_neigh


    def closest_distance(self, v1, v2):
        try:
            self.adj_list[v1][v2]
        except:
            return float('Inf')

        min_dist = float('Inf')
        for d in self.adj_list[v1][v2]:
            if d < min_dist:
                min_dist = d

        return min_dist


    def vertices(self):
        vert_set = set()
        for k in self.adj_list.keys():
            vert_set.add(k)
            for k1 in self.adj_list[k].keys():
                vert_set.add(k1)
        
        return vert_set

    def dijkstra(self, start, finish):
        vertices = self.vertices()
        distances = list()
        path_dict = dict()
        for v in vertices:
            distances.append((v, self.closest_distance(start, v)))
            path_dict[v] = None
            
        for n in self.neighbors(start):
            path_dict[n] = start

        distances.sort(key=lambda x: x[1])
        q = [x[0] for x in distances]
        distances_map = dict(distances)
        while (len(q) > 0):
            q.sort(key=lambda x: distances_map[x])
            n = q.pop(0)

            if n == finish:
                result = [n]
                parent = path_dict[n] 
                while (parent != start):
                    result.append(parent)
                    parent = path_dict[parent]
                result.append(start)
                result.reverse()
                return (result, distances_map[finish])

            for m in self.neighbors(n):
                if distances_map[n] + self.closest_distance(n, m) < distances_map[m]:
                    path_dict[m] = n
                    distances_map[m] = distances_map[n] + self.closest_distance(n,m)
