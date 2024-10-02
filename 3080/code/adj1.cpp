#include <iostream>
using namespace std;

/*
The graph G = (V,E)
Vertices: {0, 1, 2, 3}
Edges: {{0, 1},{0, 2},{1, 3}}
*/

const int NUM = 4; // Number of nodes

//function prototype
void printAdjacencyMatrix(int adjMatrix[][NUM]) ;

int main() {
    // Initialize a 2D array (adjacency matrix) with all values set to 0
    int adjMatrix[NUM][NUM] = {0};

    // Add edges
    adjMatrix[0][1] = 1; // Edge between node 0 and 1
    adjMatrix[1][0] = 1; // Edge between node 1 and 0 (since it's undirected)

    adjMatrix[0][2] = 1; // Edge between node 0 and 2
    adjMatrix[2][0] = 1; // Edge between node 2 and 0 (since it's undirected)

    adjMatrix[1][3] = 1; // Edge between node 1 and 3
    adjMatrix[3][1] = 1; // Edge between node 3 and 1 (since it's undirected)

    // Print the adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    printAdjacencyMatrix(adjMatrix);

    return 0;
}


// Function to print the adjacency matrix
void printAdjacencyMatrix(int adjMatrix[][NUM]) {
    for (int i = 0; i < NUM; ++i) {
        for (int j = 0; j < NUM; ++j) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

