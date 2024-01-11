#include <iostream>
#include <iterator>
#include <list>
using namespace std;

// function prototype
void displayAdjList(list<int> adjList[], int nodes);
void addNode(list<int> adjList[], int node, int value);

int main() {

  int nodes = 5; // there are 5 vertices in the graph

  // create an array of lists whose size is 6
  list<int> adj_list[nodes];

  addNode(adj_list, 1, 2);
  addNode(adj_list, 1, 5);

  addNode(adj_list, 2, 1);
  addNode(adj_list, 2, 5);
  addNode(adj_list, 2, 3);
  addNode(adj_list, 2, 4);

  addNode(adj_list, 3, 2);
  addNode(adj_list, 3, 4);

  addNode(adj_list, 4, 2);
  addNode(adj_list, 4, 5);
  addNode(adj_list, 4, 3);

  addNode(adj_list, 5, 4);
  addNode(adj_list, 5, 1);
  addNode(adj_list, 5, 2);

  displayAdjList(adj_list, nodes);

  return 0;
}

// function definition
void displayAdjList(list<int> adjList[], int nodes) {

  for (int i = 0; i < nodes; i++) {
    cout << i + 1 << "--->";
    list<int>::iterator it;
    for (it = adjList[i].begin(); it != adjList[i].end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
  }
}

// function definition
void addNode(list<int> adjList[], int node, int value) {

  // add v into the list u, and u into list v
  adjList[node - 1].push_back(value);
  // adj_list[v].push_back(u);
}