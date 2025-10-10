import math
class Graph:
    def __init__(self, nr_of_vertices=0, nr_of_edges=0):
        """
        Creates a graph with the given number of vertices and edges.
        """
        self.__vertices = set() 
        self.__outbounds = dict()  
        self.__inbounds = dict() 
        self.__cost = dict() 
        
        for i in range(nr_of_vertices):
            self.add_vertex(i)
    
    # 1. Get the number of vertices
    def get_nr_of_vertices(self):
        """
        Returns the number of vertices in the graph.
        """
        return len(self.__vertices)
    
    # 2. Parse (iterate) the set of vertices
    def vertices_iterator(self):
        """
        Returns an iterator for the vertices in the graph.
        """
        for vertex in self.__vertices:
            yield vertex
    
    # 3. Find out whether there is an edge between two vertices
    def is_edge(self, vertex_from, vertex_to):
        """
        Returns True if there is an edge from vertex_from to vertex_to, False otherwise.
        """
        if vertex_from not in self.__vertices or vertex_to not in self.__vertices:
            return False
        
        return vertex_to in self.__outbounds[vertex_from]
    
    # 4. Get the in degree and out degree of a specified vertex
    def get_in_degree(self, vertex_to):
        """
        Returns the in degree of a vertex.
        """
        if vertex_to not in self.__vertices:
            raise ValueError(f"Vertex {vertex_to} does not exist!")
        
        return len(self.__inbounds[vertex_to])
    
    def get_out_degree(self, vertex_from):
        """
        Returns the out degree of a vertex.
        """
        if vertex_from not in self.__vertices:
            raise ValueError(f"Vertex {vertex_from} does not exist!")
        
        return len(self.__outbounds[vertex_from])
    
    # 5. Parse (iterate) the set of outbound edges of a specified vertex
    def outbound_iterator(self, vertex_from):
        """
        Returns an iterator for the outbound edges of a vertex.
        """
        if vertex_from not in self.__vertices:
            raise ValueError(f"Vertex {vertex_from} does not exist!")
        
        for vertex_to in self.__outbounds[vertex_from]:
            yield vertex_to
    
    # 6. Parse the set of inbound edges of a specified vertex
    def inbound_iterator(self, vertex_to):
        """
        Returns an iterator for the inbound edges of a vertex.
        """
        if vertex_to not in self.__vertices:
            raise ValueError(f"Vertex {vertex_to} does not exist!")
        
        for vertex_from in self.__inbounds[vertex_to]:
            yield vertex_from
    
    # 7. Get the endpoints of an edge (represented as pairs of vertices)
    def edges_iterator(self):
        """
        Returns an iterator for the edges in the graph.
        Each edge is represented as a tuple (vertex_from, vertex_to).
        """
        for edge in self.__cost.keys():
            yield edge
    
    # 8. Retrieve or modify the information (integer) attached to a specified edge
    def get_cost(self, vertex_from, vertex_to):
        """
        Returns the cost of an edge.
        Throws an exception if the edge does not exist.
        """
        if not self.is_edge(vertex_from, vertex_to):
            raise ValueError(f"Edge from {vertex_from} to {vertex_to} does not exist!")
        
        return self.__cost[(vertex_from, vertex_to)]
    
    def set_cost(self, vertex_from, vertex_to, new_cost):
        """
        Sets the cost of an edge.
        Throws an exception if the edge does not exist.
        """
        if not self.is_edge(vertex_from, vertex_to):
            raise ValueError(f"Edge from {vertex_from} to {vertex_to} does not exist!")
        
        self.__cost[(vertex_from, vertex_to)] = new_cost
    
    # 9. The graph shall be modifiable (add/remove edges and vertices)
    def add_vertex(self, vertex_to_be_added):
        """
        Adds a vertex to the graph.
        Throws an exception if the vertex already exists.
        """
        if vertex_to_be_added in self.__vertices:
            raise ValueError(f"Vertex {vertex_to_be_added} already exists!")
        
        self.__vertices.add(vertex_to_be_added)
        self.__outbounds[vertex_to_be_added] = set()
        self.__inbounds[vertex_to_be_added] = set()
    
    def remove_vertex(self, vertex_to_be_removed):
        """
        Removes a vertex from the graph.
        Throws an exception if the vertex does not exist.
        """
        if vertex_to_be_removed not in self.__vertices:
            raise ValueError(f"Vertex {vertex_to_be_removed} does not exist!")
        
        outbound_edges = list(self.__outbounds[vertex_to_be_removed])
        for out_vertex in outbound_edges:
            self.remove_edge(vertex_to_be_removed, out_vertex)
        
        inbound_edges = list(self.__inbounds[vertex_to_be_removed])
        for in_vertex in inbound_edges:
            self.remove_edge(in_vertex, vertex_to_be_removed)
        
        self.__vertices.remove(vertex_to_be_removed)
        del self.__outbounds[vertex_to_be_removed]
        del self.__inbounds[vertex_to_be_removed]
    
    def add_edge(self, vertex_from, vertex_to, edge_cost):
        """
        Adds an edge to the graph.
        Throws an exception if the edge already exists or if one of the vertices does not exist.
        """
        if vertex_from not in self.__vertices:
            raise ValueError(f"Vertex {vertex_from} does not exist!")
        
        if vertex_to not in self.__vertices:
            raise ValueError(f"Vertex {vertex_to} does not exist!")
        
        if self.is_edge(vertex_from, vertex_to):
            raise ValueError(f"Edge from {vertex_from} to {vertex_to} already exists!")
        
        self.__outbounds[vertex_from].add(vertex_to)
        self.__inbounds[vertex_to].add(vertex_from)
        self.__cost[(vertex_from, vertex_to)] = edge_cost
    
    def remove_edge(self, vertex_from, vertex_to):
        """
        Removes an edge from the graph.
        Throws an exception if the edge does not exist.
        """
        if not self.is_edge(vertex_from, vertex_to):
            raise ValueError(f"Edge from {vertex_from} to {vertex_to} does not exist!")
        
        self.__outbounds[vertex_from].remove(vertex_to)
        self.__inbounds[vertex_to].remove(vertex_from)
        del self.__cost[(vertex_from, vertex_to)]
    
    # 10. The graph shall be copyable
    def copy(self):
        """
        Returns a copy of the graph.
        """
        new_graph = Graph()
        
        for vertex in self.__vertices:
            new_graph.add_vertex(vertex)
        
        for vertex_from, vertex_to in self.__cost.keys():
            new_graph.add_edge(vertex_from, vertex_to, self.__cost[(vertex_from, vertex_to)])
        
        return new_graph
    
    # Additional methods
    def is_vertex(self, vertex_to_be_checked):
        """
        Returns True if the vertex_to_be_checked is a vertex in the graph, False otherwise.
        """
        return vertex_to_be_checked in self.__vertices
    
    def get_nr_of_edges(self):
        """
        Returns the number of edges in the graph.
        """
        return len(self.__cost)
    
    #METHODS FOR HW 3::::::::::::

    def __build_cost_matrix(self):
        """
        Builds and returns the initial cost matrix W (D^1) from the graph.
        """
        n = self.get_nr_of_vertices()
        W = [[math.inf for _ in range(n)] for _ in range(n)]

        for i in self.__vertices:
            W[i][i] = 0  # Distance from a node to itself is 0

        for (u, v) in self.__cost:
            W[u][v] = self.__cost[(u, v)]

        return W

    def __extend(self, D, W):
        """
        Min-plus matrix multiplication (EXTEND function).
        D and W are both n x n matrices.
        """
        n = self.get_nr_of_vertices()
        new_D = [[math.inf for _ in range(n)] for _ in range(n)]

        for i in range(n):
            for j in range(n):
                for k in range(n):
                    new_D[i][j] = min(new_D[i][j], D[i][k] + W[k][j])

        return new_D

    def slow_apsp(self):
        """
        SLOW-APSP: Computes shortest paths between all pairs of vertices
        using repeated min-plus matrix multiplication.
        """
        W = self.__build_cost_matrix()
        D = W

        for _ in range(self.get_nr_of_vertices() - 1):
            D = self.__extend(D, W)

        # Check for negative-cost cycles
        for i in range(self.get_nr_of_vertices()):
            if D[i][i] < 0:
                return None  # Negative cycle detected

        return D

    def lowest_cost_walk(self, start, end):
        """
        Returns the cost of the lowest-cost walk from start to end.
        Detects negative-cost cycles.
        """
        if not self.is_vertex(start) or not self.is_vertex(end):
            raise ValueError("Start or end vertex does not exist.")

        D = self.slow_apsp()

        if D is None:
            print("The graph contains a negative-cost cycle.")
        elif D[start][end] == math.inf:
            print(f"No path from {start} to {end}.")
        else:
            print(f"Lowest cost from {start} to {end} is {D[start][end]}.")

    #METHODS FOR A4     
    
    def is_dag(self):
        """
        Returns True if the graph is a Directed Acyclic Graph (DAG), False otherwise.
        Uses DFS-based cycle detection.
        """
        visited = set()
        recursion_stack = set()
        
        def has_cycle(v):
            visited.add(v)
            recursion_stack.add(v)
            
            for neighbor in self.__outbounds[v]:
                if neighbor not in visited:
                    if has_cycle(neighbor):
                        return True
                elif neighbor in recursion_stack:
                    return True
            
            recursion_stack.remove(v)
            return False
        
        for vertex in self.__vertices:
            if vertex not in visited:
                if has_cycle(vertex):
                    return False
        return True
    
    def topological_sort(self):
        """
        Returns a topological sort of the vertices if the graph is a DAG.
        Uses DFS-based approach (Tarjan's algorithm).
        Raises an exception if the graph is not a DAG.
        """
        if not self.is_dag():
            raise ValueError("Graph is not a DAG, cannot perform topological sort")
        
        visited = set()
        stack = []
        
        def dfs(v):
            visited.add(v)
            for neighbor in self.__outbounds[v]:
                if neighbor not in visited:
                    dfs(neighbor)
            stack.append(v)
        
        for vertex in self.__vertices:
            if vertex not in visited:
                dfs(vertex)
        
        return stack[::-1]  # Return in reverse order
    
    def highest_cost_path(self, start, end):
        """
        Finds the highest cost path between two vertices in a DAG.
        Returns a tuple of (cost, path) where path is a list of vertices.
        Works in O(m+n) time for DAGs using topological sorting.
        """
        if not self.is_dag():
            raise ValueError("Graph is not a DAG, cannot find highest cost path")
        if start not in self.__vertices or end not in self.__vertices:
            raise ValueError("Start or end vertex does not exist")
        
        top_order = self.topological_sort()
        dist = {v: -math.inf for v in self.__vertices}
        dist[start] = 0
        parent = {v: None for v in self.__vertices}
        
        for u in top_order:
            if dist[u] != -math.inf:
                for v in self.__outbounds[u]:
                    if dist[v] < dist[u] + self.__cost[(u, v)]:
                        dist[v] = dist[u] + self.__cost[(u, v)]
                        parent[v] = u
        
        if dist[end] == -math.inf:
            return (None, [])  # No path exists
        
        # Reconstruct path
        path = []
        current = end
        while current is not None:
            path.append(current)
            current = parent[current]
        path.reverse()
        
        return (dist[end], path)
    
    #LAST HOMEWORK
    def find_hamiltonian_cycle(self):
        """
        Attempts to find a Hamiltonian cycle in the graph.
        Returns the cycle as a list if found, otherwise None.
        This treats the graph as undirected (for symmetry).
        """
        n = self.get_nr_of_vertices()
        vertices = list(self.vertices_iterator())

        # Build undirected adjacency matrix
        adj_matrix = [[0 for _ in range(n)] for _ in range(n)]
        for v in vertices:
            for u in self.outbound_iterator(v):
                adj_matrix[v][u] = 1
                adj_matrix[u][v] = 1  # Treat as undirected

        path = [-1] * n
        path[0] = 0  # Start at vertex 0

        def is_valid(v, pos):
            if adj_matrix[path[pos - 1]][v] == 0:
                return False
            if v in path:
                return False
            return True

        def backtrack(pos):
            if pos == n:
                return adj_matrix[path[pos - 1]][path[0]] == 1
            for v in range(1, n):
                if is_valid(v, pos):
                    path[pos] = v
                    if backtrack(pos + 1):
                        return True
                    path[pos] = -1 
            return False

        if backtrack(1):
            path.append(path[0])  # Complete the cycle
            return path
        else:
            return None
