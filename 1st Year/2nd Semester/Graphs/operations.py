import random

# 11. Read the graph from a text file
def read_graph_from_file(file_path):
    """
    Reads a graph from a file.
    """
    from graph import Graph
    
    with open(file_path, 'r') as file:
        first_line = file.readline().strip().split()
        nr_of_vertices = int(first_line[0])
        nr_of_edges = int(first_line[1])
        
        graph = Graph(nr_of_vertices)
        
        for _ in range(nr_of_edges):
            line = file.readline().strip().split()
            vertex_from = int(line[0])
            vertex_to = int(line[1])
            cost = int(line[2])
            
            try:
                graph.add_edge(vertex_from, vertex_to, cost)
            except ValueError as e:
                print(f"Warning: {e}")
    
    return graph

# 12. Write the graph to a text file
def save_graph_to_file(graph, file_path):
    """
    Saves a graph to a file.
    """
    with open(file_path, 'w') as file:
        file.write(f"{graph.get_nr_of_vertices()} {graph.get_nr_of_edges()}\n")
        
        for edge in graph.edges_iterator():
            vertex_from, vertex_to = edge
            cost = graph.get_cost(vertex_from, vertex_to)
            file.write(f"{vertex_from} {vertex_to} {cost}\n")

# 13. Create a random graph with specified number of vertices and edges
def generate_random_graph(nr_of_vertices, nr_of_edges):
    """
    Generates a random graph with the given number of vertices and edges.
    """
    from graph import Graph
    
    if nr_of_vertices <= 0:
        raise ValueError("Number of vertices must be positive!")
    
    max_edges = nr_of_vertices * nr_of_vertices
    if nr_of_edges > max_edges:
        print(f"Too many edges! Maximum is {max_edges} for {nr_of_vertices} vertices.")
        nr_of_edges = max_edges
    
    graph = Graph(nr_of_vertices)
    
    added_edges = 0
    while added_edges < nr_of_edges:
        vertex_from = random.randint(0, nr_of_vertices - 1)
        vertex_to = random.randint(0, nr_of_vertices - 1)
        cost = random.randint(-100, 100)
        
        if not graph.is_edge(vertex_from, vertex_to):
            graph.add_edge(vertex_from, vertex_to, cost)
            added_edges += 1
    
    return graph, nr_of_edges