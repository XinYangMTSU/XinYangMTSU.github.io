#include <iostream>
#include <vector>
using namespace std;

/*
G = (V,E)
Vertices: {1, 2, 3, 4}
Edges: {{1,2}, {2,3}, {3,4}, {4,1}}
*/

// Struct to represent an entry in the adjacency list
// Each record stores the node and a "pseudopointer" (index) to the next adjacent node in the adjacency list.
struct Node {
    int vertex;  // The adjacent vertex
    int next;    // Index of the next vertex in the adjacency list (pseudopointer)
};

int main() {
    // Define the size of the graph (4 vertices)
    const int vertices = 4;

    // Arrays to represent the adjacency list with pseudopointers
    vector<Node> adj = {
        {2, -1},  // Vertex 1 → Vertex 2 (no further adjacent nodes)
        {3, -1},  // Vertex 2 → Vertex 3 (no further adjacent nodes)
        {4, -1},  // Vertex 3 → Vertex 4 (no further adjacent nodes)
        {1, -1},  // Vertex 4 → Vertex 1 (cycle back to Vertex 1, no further adjacent nodes)
        
        // The placeholder nodes are no longer necessary as there is only one adjacent node per vertex
    };

    // Array to store the index of the head of the adjacency list for each vertex
    int head[vertices] = {0, 1, 2, 3};

    // Corrected loop to display the correct adjacency list
    for (int i = 0; i < vertices; ++i) {
        cout << "Vertex " << i + 1 << ": " << i + 1;

        // Using the corrected pseudopointer logic
        for (int index = head[i]; index != -1; index = adj[index].next) {
            cout << " -> " << adj[index].vertex;
        }

        cout << endl;
    }

    return 0;
}
