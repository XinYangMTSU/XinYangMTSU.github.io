// C++ program for tree traversals InOrder algorithms
#include <iostream>
using namespace std;

// A tree node has data, pointer to left child , a pointer to middle child, and
// a pointer to right child
struct Node {
  char data;
  Node *left, *middle, *right;
};

// function prototype
// create a new tree node
Node *newNode(char data);
// given a treee, print its nodes in inorder
void printInorder(Node *node);
// Delete the tree and free memory
void deleteTree(Node *node);      

// Driver code
int main() {
    
  Node *a = newNode('a');
  Node *b = newNode('b');
  Node *c = newNode('c');
  Node *d = newNode('d');
  Node *e = newNode('e');
  Node *f = newNode('f');
  Node *g = newNode('g');
  Node *h = newNode('h');
  Node *i = newNode('i');
  Node *j = newNode('j');
  Node *k = newNode('k');
    
    // create root node
  Node *root = a;
  a->left = b;
  a->right = c;

  // add left, middle and right node for node b
  b->left = d;
  b->middle = e;
  b->right = f;

  // add middle node for d
  d->left = i; // change it if needed

  // add left and right node for c
  c->left = g;
  c->right = h;

  // add left and right node for g
  g->left = j;
  g->right = k;

  // Function call
  cout << "Inorder traversal of your tree is " << endl;
  printInorder(root);
  cout << endl;
 

    // Delete the tree and free memory
    deleteTree(root);
    
    return 0;
}

// function definition to create a new tree node
Node *newNode(char data) {

  //Dynamically allocates memory for new nodes.
  Node *temp = new Node;
  temp->data = data;
  temp->left = temp->middle = temp->right = NULL;
    
  return temp;
}


// Given a tree, print its nodes in inorder
void printInorder(Node *node) {

  if (node == NULL) {
    return;
  }

  // First recur on left child
  printInorder(node->left);

  // Then print the data of node
  // print the root
  cout << node->data << " ";

  // Now recur on middle child
  printInorder(node->middle);

  // Nor recur on right child
  printInorder(node->right);
}

// Function to delete the entire tree
void deleteTree(Node *node) {
    
    if (node == NULL) {
        return;
    }

    // Recursively delete left, middle, and right children
    deleteTree(node->left);
    deleteTree(node->middle);
    deleteTree(node->right);

    // Delete the current node
    cout << "Deleting node: " << node->data << endl;
    delete node;
}