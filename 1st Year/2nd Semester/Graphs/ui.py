from graph import Graph
from operations import generate_random_graph, read_graph_from_file, save_graph_to_file

class UI:
    def __init__(self):
        self.__graph = None
        self.__commands = {
           "1": self.__get_number_of_vertices,
            "2": self.__list_all_vertices,
            "3": self.__check_if_edge_exists,
            "4": self.__get_in_degree,
            "5": self.__get_out_degree,
            "6": self.__list_outbound_edges,
            "7": self.__list_inbound_edges,
            "8": self.__list_all_edges,
            "9": self.__get_edge_cost,
            "10": self.__set_edge_cost,
            "11": self.__add_vertex,
            "12": self.__remove_vertex,
            "13": self.__add_edge,
            "14": self.__remove_edge,
            "15": self.__copy_graph,
            "16": self.__load_graph_from_file,
            "17": self.__save_graph_to_file,
            "18": self.__create_random_graph,
            "19": self.__create_empty_graph,
            "20": self.__get_number_of_edges,
            "21": self.__test_copy,
            "22": self.__depth_first,
            "23": self.__matrix_mul,
            "24": self.__is_dag,
            "25": self.__topological_sort,
            "26": self.__highest_cost_path,
            "27": self.__find_hamiltonian_cycle,
            "0": self.__exit
        }
        self.__graph = Graph()  
    
    def run(self):
        """
        Runs the console application.
        """
        while True:
            self.__print_menu()
            command = input("Enter command: ")
            
            if command in self.__commands:
                try:
                    self.__commands[command]()
                except Exception as e:
                    print(f"Error: {e}")
            else:
                print("Invalid command!")
    
    def __print_menu(self):
        """
        Prints the menu.
        """
        print("\nWelcome to the Directed Graph Application")
        print("Choose one of the options below:")
        print("1. Get the number of vertices")
        print("2. List all vertices")
        print("3. Check if an edge exists")
        print("4. Get the in degree of a vertex")
        print("5. Get the out degree of a vertex")
        print("6. List outbound edges of a vertex")
        print("7. List inbound edges of a vertex")
        print("8. List all edges")
        print("9. Get the cost of an edge")
        print("10. Set the cost of an edge")
        print("11. Add a vertex")
        print("12. Remove a vertex")
        print("13. Add an edge")
        print("14. Remove an edge")
        print("15. Create a copy of the graph")
        print("16. Load a graph from file")
        print("17. Save the graph to file")
        print("18. Create a random graph")
        print("19. Create an empty graph")
        print("20. Get the number of edges")
        print("21. Test graph copy")
        print("22. Find connected components (DFS)")
        print("23. Find lowest cost walk (Matrix multiplication)")
        print("24. Check if graph is a DAG")
        print("25. Perform topological sort (for DAGs)")
        print("26. Find highest cost path between two vertices (for DAGs)")
        print("27. Find a Hamiltonian cycle (if one exists)")
        print("0. Exit")
    
    # 1. Get the number of vertices
    def __get_number_of_vertices(self):
        """
        Gets the number of vertices in the graph.
        """
        print(f"There are {self.__graph.get_nr_of_vertices()} vertices.")
    
    # 2. Parse (iterate) the set of vertices
    def __list_all_vertices(self):
        """
        Lists all vertices in the graph.
        """
        vertices = list(self.__graph.vertices_iterator())
        print(f"Vertices: {vertices}")
    
    # 3. Find out whether there is an edge between two vertices
    def __check_if_edge_exists(self):
        """
        Checks if an edge exists in the graph.
        """
        vertex_from = int(input("Enter source vertex: "))
        vertex_to = int(input("Enter target vertex: "))
        
        if self.__graph.is_edge(vertex_from, vertex_to):
            cost = self.__graph.get_cost(vertex_from, vertex_to)
            print(f"Edge from {vertex_from} to {vertex_to} exists with cost {cost}.")
        else:
            print(f"Edge from {vertex_from} to {vertex_to} does not exist.")
    
    # 4a. Get the in degree of a vertex
    def __get_in_degree(self):
        """
        Gets the in degree of a vertex.
        """
        vertex = int(input("Enter vertex: "))
        in_degree = self.__graph.get_in_degree(vertex)
        print(f"In degree of vertex {vertex}: {in_degree}")
    
    # 4b. Get the out degree of a vertex
    def __get_out_degree(self):
        """
        Gets the out degree of a vertex.
        """
        vertex = int(input("Enter vertex: "))
        out_degree = self.__graph.get_out_degree(vertex)
        print(f"Out degree of vertex {vertex}: {out_degree}")
    
    # 5. Parse the set of outbound edges
    def __list_outbound_edges(self):
        """
        Lists the outbound edges of a vertex.
        """
        vertex = int(input("Enter vertex: "))
        outbound_vertices = list(self.__graph.outbound_iterator(vertex))
        
        if not outbound_vertices:
            print(f"No outbound edges for vertex {vertex}.")
            return
        
        print(f"Outbound edges for vertex {vertex}:")
        for out_vertex in outbound_vertices:
            cost = self.__graph.get_cost(vertex, out_vertex)
            print(f"To {out_vertex} - Cost: {cost}")
    
    # 6. Parse the set of inbound edges
    def __list_inbound_edges(self):
        """
        Lists the inbound edges of a vertex.
        """
        vertex = int(input("Enter vertex: "))
        inbound_vertices = list(self.__graph.inbound_iterator(vertex))
        
        if not inbound_vertices:
            print(f"No inbound edges for vertex {vertex}.")
            return
        
        print(f"Inbound edges for vertex {vertex}:")
        for in_vertex in inbound_vertices:
            cost = self.__graph.get_cost(in_vertex, vertex)
            print(f"From {in_vertex} - Cost: {cost}")
    
    # 7. Get the endpoints of edges
    def __list_all_edges(self):
        """
        Lists all edges in the graph.
        """
        edges = list(self.__graph.edges_iterator())
        if not edges:
            print("No edges in the graph.")
            return
        
        print("Edges:")
        for edge in edges:
            vertex_from, vertex_to = edge
            cost = self.__graph.get_cost(vertex_from, vertex_to)
            print(f"({vertex_from}, {vertex_to}) - Cost: {cost}")
    
    # 8a. Retrieve information attached to an edge
    def __get_edge_cost(self):
        """
        Gets the cost of an edge.
        """
        vertex_from = int(input("Enter source vertex: "))
        vertex_to = int(input("Enter target vertex: "))
        
        cost = self.__graph.get_cost(vertex_from, vertex_to)
        print(f"Cost of edge from {vertex_from} to {vertex_to}: {cost}")
    
    # 8b. Modify information attached to an edge
    def __set_edge_cost(self):
        """
        Sets the cost of an edge.
        """
        vertex_from = int(input("Enter source vertex: "))
        vertex_to = int(input("Enter target vertex: "))
        new_cost = int(input("Enter new cost: "))
        
        self.__graph.set_cost(vertex_from, vertex_to, new_cost)
        print(f"Cost of edge from {vertex_from} to {vertex_to} set to {new_cost}.")
    
    # 9a. Add a vertex
    def __add_vertex(self):
        """
        Adds a vertex to the graph.
        """
        vertex = int(input("Enter vertex to add: "))
        self.__graph.add_vertex(vertex)
        print(f"Vertex {vertex} added.")
    
    # 9b. Remove a vertex
    def __remove_vertex(self):
        """
        Removes a vertex from the graph.
        """
        vertex = int(input("Enter vertex to remove: "))
        self.__graph.remove_vertex(vertex)
        print(f"Vertex {vertex} removed.")
    
    # 9c. Add an edge
    def __add_edge(self):
        """
        Adds an edge to the graph.
        """
        vertex_from = int(input("Enter source vertex: "))
        vertex_to = int(input("Enter target vertex: "))
        cost = int(input("Enter edge cost: "))
        
        self.__graph.add_edge(vertex_from, vertex_to, cost)
        print(f"Edge from {vertex_from} to {vertex_to} with cost {cost} added.")
    
    # 9d. Remove an edge
    def __remove_edge(self):
        """
        Removes an edge from the graph.
        """
        vertex_from = int(input("Enter source vertex: "))
        vertex_to = int(input("Enter target vertex: "))
        
        self.__graph.remove_edge(vertex_from, vertex_to)
        print(f"Edge from {vertex_from} to {vertex_to} removed.")
    
    # 10. Copy the graph
    def __copy_graph(self):
        """
        Creates a copy of the graph.
        """
        new_graph = self.__graph.copy()
        print(f"Graph copied. Original graph has {self.__graph.get_nr_of_vertices()} vertices and {self.__graph.get_nr_of_edges()} edges.")
        print(f"New graph has {new_graph.get_nr_of_vertices()} vertices and {new_graph.get_nr_of_edges()} edges.")
        return new_graph
    
    # 11. Read the graph from a file
    def __load_graph_from_file(self):
        """
        Loads a graph from a file.
        """
        file_path = input("Enter file path: ")
        self.__graph = read_graph_from_file(file_path)
        print(f"Graph loaded from {file_path}.")
    
    # 12. Write the graph to a file
    def __save_graph_to_file(self):
        """
        Saves the graph to a file.
        """
        file_path = input("Enter file path: ")
        save_graph_to_file(self.__graph, file_path)
        print(f"Graph saved to {file_path}.")
    
    # 13. Create a random graph
    def __create_random_graph(self):
        """
        Creates a random graph.
        """
        nr_of_vertices = int(input("Enter number of vertices: "))
        nr_of_edges = int(input("Enter number of edges: "))
        
        self.__graph, nr_of_edges = generate_random_graph(nr_of_vertices, nr_of_edges)
        print(f"Random graph with {nr_of_vertices} vertices and {nr_of_edges} edges created.")
    
    # Additional methods
    def __create_empty_graph(self):
        """
        Creates an empty graph.
        """
        self.__graph = Graph()
        print("Empty graph created.")
    
    def __get_number_of_edges(self):
        """
        Gets the number of edges in the graph.
        """
        print(f"Number of edges: {self.__graph.get_nr_of_edges()}")

    def __test_copy(self):
        new_graph = self.__graph.copy()
        print("Original graph before:")
        print(self.__graph.get_nr_of_vertices())
        print("Copy before:")
        print(new_graph.get_nr_of_vertices())
        new_graph.remove_vertex(1)
        new_graph.remove_vertex(2)
        print("Original graph after modifying the copy:")
        print(self.__graph.get_nr_of_vertices())
        print("The copy:")
        print(new_graph.get_nr_of_vertices())

    def __depth_first(self):
        """
        Finds all connected components in an undirected graph using DFS.
        Treats the directed graph as undirected by considering both inbound and outbound edges.
        Also creates separate graphs for each component and prints their details.
        """
        if self.__graph is None:
            print("No graph loaded. Please create or load a graph first.")
            return
        
        visited = set()
        components = []
        
        for vertex in self.__graph.vertices_iterator():
            if vertex not in visited:
                component = set()
                self.__dfs_visit(vertex, visited, component)
                components.append(component)
        
        print(f"Found {len(components)} connected components:")
        component_graphs = []
        
        for i, component in enumerate(components, 1):
            print(f"Component {i}: {sorted(list(component))}")
            
            component_graph = Graph()
            for vertex in component:
                component_graph.add_vertex(vertex)
            
            for v1 in component:
                for v2 in component:
                    if self.__graph.is_edge(v1, v2):
                        cost = self.__graph.get_cost(v1, v2)
                        component_graph.add_edge(v1, v2, cost)
            
            component_graphs.append(component_graph)

            print(f"  Component {i} has {component_graph.get_nr_of_vertices()} vertices and {component_graph.get_nr_of_edges()} edges")
            
            vertices = list(component_graph.vertices_iterator())
            print(f"  Vertices: {vertices}")
            
            edges = list(component_graph.edges_iterator())
            if edges:
                print(f"  Edges:")
                for edge in edges:
                    vertex_from, vertex_to = edge
                    cost = component_graph.get_cost(vertex_from, vertex_to)
                    print(f"    ({vertex_from}, {vertex_to}) - Cost: {cost}")
            else:
                print("  No edges in this component")
            print()  
        return components, component_graphs

    def __dfs_visit(self, vertex, visited, component):
        """
        Helper method for depth-first traversal.
        
        Args:
            vertex: The current vertex being visited
            visited: Set of vertices that have been visited
            component: The current connected component being built
        """
        visited.add(vertex)
        component.add(vertex)
        
        for neighbor in self.__graph.outbound_iterator(vertex):
            if neighbor not in visited:
                self.__dfs_visit(neighbor, visited, component)
        
        for neighbor in self.__graph.inbound_iterator(vertex):
            if neighbor not in visited:
                self.__dfs_visit(neighbor, visited, component)

    def __matrix_mul(self):
        """
        Finds a lowest cost walk between the given vertices, or prints a message if there are negative cost cycles in the graph
        """
        while True:
            try:
                start = int(input("Enter the start vertex: "))
                target = int(input("Enter the target vertex: "))
                break
            except Exception as e:
                print(f"Error: {e}")
        self.__graph.lowest_cost_walk(start, target)


    def __is_dag(self):
        """
        Checks if the current graph is a Directed Acyclic Graph (DAG).
        """
        if self.__graph.is_dag():
            print("The graph is a DAG (Directed Acyclic Graph).")
        else:
            print("The graph is NOT a DAG (contains cycles).")
    
    def __topological_sort(self):
        """
        Performs topological sorting of the graph if it's a DAG.
        """
        try:
            top_order = self.__graph.topological_sort()
            print("Topological order:", top_order)
        except ValueError as e:
            print(f"Error: {e}")
    
    def __highest_cost_path(self):
        """
        Finds the highest cost path between two vertices in a DAG.
        """
        try:
            start = int(input("Enter start vertex: "))
            end = int(input("Enter end vertex: "))
            
            cost, path = self.__graph.highest_cost_path(start, end)
            
            if cost is None:
                print(f"No path exists from {start} to {end}.")
            else:
                print(f"Highest cost path from {start} to {end}:")
                print(f"Total cost: {cost}")
                print("Path:", " → ".join(map(str, path)))
        except ValueError as e:
            print(f"Error: {e}")
        except Exception as e:
            print(f"An error occurred: {e}")

    def __find_hamiltonian_cycle(self):
        """
        Attempts to find a Hamiltonian cycle in the graph.
        """
        cycle = self.__graph.find_hamiltonian_cycle()
        if cycle is None:
            print("No Hamiltonian cycle found.")
        else:
            print("Hamiltonian cycle found:")
            print(" → ".join(map(str, cycle)))

    def __exit(self):
        """
        Exits the application.
        """
        print("Goodbye!")
        exit(0)