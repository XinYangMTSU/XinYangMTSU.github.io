#include <iostream>
#include <list>
using namespace std;

/*
G = (V,E)
V: {0,1,2,3,4}
E: {{0,1},{0,4},{1,2},{1,3},{1,4},{2,3},{3,4}}

Adj List:
0: 0 -> 1 -> 4 -> nullptr
1: 1 -> 0 -> 2 -> 3 -> 4 -> nullptr
2: 2 -> 1 -> 3 -> nullptr
3: 3 -> 1 -> 2 -> 4 -> nullptr
4: 4 -> 0 -> 1 -> 3 -> nullptr

*/

//Defines a class named Graph that represents a graph using an adjacency list. 
class Graph {
    //data members
    int numVertices;
    list<int>* adjLists; // Pointer to an array containing adjacency lists
    //adjLists[i] contains a list of integers representing all the vertices connected to vertex i.
public:
    //The constructor typically allocates memory for the adjacency list and sets up the graph's initial state.
    Graph(int V);
    //This method adds an edge between two vertices src and dest.
    void addEdge(int src, int dest);
    //This method prints the adjacency list of the graph.
    void printGraph();
};

// Constructor
Graph::Graph(int V) {
    numVertices = V;
    adjLists = new list<int>[V];
}

// Add edges
void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src); // Since it's an undirected graph
}

// Print the adjacency list representation of the graph
void Graph::printGraph() {
    for (int i = 0; i < numVertices; ++i) {
        cout << i << ": " << i << " -> ";
        for (auto v : adjLists[i]) {
            cout << v << " -> ";
        }
        cout << "nullptr" << endl;
    }
}

// main function
int main() {
    
    //This creates a graph with 5 vertices
    Graph g(5);

    //Adds an undirected edge between vertex 1 and vertex 2. In the adjacency list, vertex 1 will list vertex 2 as a neighbor, and vice versa.
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printGraph();

    return 0;
}


