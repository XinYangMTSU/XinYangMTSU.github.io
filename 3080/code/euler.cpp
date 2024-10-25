/*
Purpose of the Code
=====================
Euler Path Condition: To determine if an Euler path exists, a graph should have exactly 0 or 2 vertices with an odd degree:

0 Odd-Degree Vertices: Euler circuit exists (path starts and ends at the same vertex).
2 Odd-Degree Vertices: Euler path exists (path starts at one odd-degree vertex and ends at the other).
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Function to find and print Eulerian Path using Hierholzer’s Algorithm
void printEulerPath(vector<vector<int>>& graph) {
    
    //odd keeps track of the number of vertices with an odd degree.
    //start is initialized to 0 and will eventually hold the index of the starting vertex for the Euler path (or circuit).
    //n stores the size of the graph (number of vertices).
    int odd = 0, start = 0, n = graph.size();
    
    //Degree Calculation Loop for each vertex
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            degree += graph[i][j];
        }
        //Odd Degree Check
        if (degree % 2 != 0) {
            odd++;
            start = i;
        }
    }

    // If there are no or exactly two odd vertices, Euler path exists.
    if (odd != 0 && odd != 2) {
        cout << "There are " << odd << " odd nodes in the graph." << endl; 
        cout << "The graph doesn't have an Euler Path." << endl;
        return;
    }

    //Hierholzer’s Algorithm:
    //This piece of code implements Hierholzer's Algorithm to find an Euler path or circuit in a graph. Hierholzer's Algorithm works by exploring edges from each vertex, ensuring that every edge is used exactly once in the traversal.
    
    stack<int> curr_path; //A stack used to store the current path being traversed in the graph.
    vector<int> circuit; //A vector that will store the final Euler path or circuit.
    curr_path.push(start); //The starting vertex for the Euler traversal

    while (!curr_path.empty()) {
        int u = curr_path.top();
        bool found = false;
        //Iterates through potential connections (v vertices) from the current vertex u.
        for (int v = 0; v < n; v++) {
            //Edge Check
            //If there’s an edge between u and v (graph[u][v]>0),the algorithm moves to v.
            if (graph[u][v]) {
                curr_path.push(v); //marking v as the next step in traversal.
                graph[u][v]--; //The edge between u and v is decremented to ensure each edge is used only once.
                graph[v][u]--;
                found = true; // found is set to true to indicate a path was found.
                break;
            }
        }
        //If no more edges are available from u (found == false), u is added to circuit,
        if (!found) {
            circuit.push_back(u);
            curr_path.pop();
        }
    }

    // Print the Euler Path
    cout << "There are " << odd << " odd nodes in the graph. Euler path exists." << endl; 
    cout << "Euler Path: ";
    for (int i = circuit.size() - 1; i > 0; i--) {
        cout << circuit[i] << " -> ";
    }
    cout << circuit[0] << endl;
}

int main() {
    // Define the graph as an adjacency matrix
    vector<vector<int>> graph = {
        {0, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 1, 1, 1, 0}
    };

    printEulerPath(graph);

    return 0;
}
