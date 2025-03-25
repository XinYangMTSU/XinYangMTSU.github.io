#include <iostream>
#include <vector>
#include <fstream>
using namespace std;                

// Function declarations
void inputMatrixFromFile(const string& filename, vector<vector<int>> &adjMatrix);
void printMatrix(const vector<vector<int>>& matrix);
vector<vector<int>> booleanMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B);
vector<vector<int>> computeReachabilityByMultiplication(vector<vector<int>> &adjMatrix) ;
vector<vector<int>> computeReachabilityByWarshall(vector<vector<int>> &adjMatrix);

int main() {
    
    string filename;
    // Create a 2D adjacency matrix initialized with zeros
    vector<vector<int>> adjMatrix;

    // Prompt user to enter the filename containing the adjacency matrix
    cout << "Enter the filename containing the adjacency matrix: ";
    cin >> filename;

    // Load the matrix from the file
    inputMatrixFromFile(filename, adjMatrix);

    // Compute and display the reachability matrix using Boolean multiplication
    cout << "\nReachability Matrix (Method 1 - Boolean Multiplication):\n";
    vector<vector<int>> reachMatrix1 = computeReachabilityByMultiplication(adjMatrix);
    printMatrix(reachMatrix1);

    // Compute and display the reachability matrix using Warshall's Algorithm
    cout << "\nReachability Matrix (Method 2 - Warshall's Algorithm):\n";
    vector<vector<int>> reachMatrix2 = computeReachabilityByWarshall(adjMatrix);
    printMatrix(reachMatrix2);

    return 0;
}

// Reads an adjacency matrix from a file into the given 2D vector
void inputMatrixFromFile(const string& filename, vector<vector<int>> &adjMatrix) {
    int numNodes;
    ifstream file;
    file.open(filename);
    
    if (!file) {
        cerr << "Error: Cannot open file " << filename << "\n";
        exit(1);
    }

    // Read the number of nodes from the first line of the file.
    file >> numNodes;
    // Resize the 2D vector 'adjMatrix' to be a square matrix with 'numNodes' rows and 'numNodes' columns, all default-initialized to 0.
    adjMatrix.resize(numNodes, vector<int>(numNodes));
    
    // Read matrix values row by row
    for (int i = 0; i < numNodes; ++i)
        for (int j = 0; j < numNodes; ++j)
            file >> adjMatrix[i][j];

    file.close();
}

// Prints a 2D matrix in row-column format
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row)
            cout << val << " ";
        cout << "\n";
    }
}

// Performs Boolean matrix multiplication (AND for multiply, OR for sum)
vector<vector<int>> booleanMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int numNodes = A.size();
    //Initialization 
    vector<vector<int>> result(numNodes, vector<int>(numNodes, 0));
    
    //Boolean Matrix Multiplication 
    //It uses AND (&) for multiply, and OR (|) for sum operations.
    for (int i = 0; i < numNodes; ++i)
        for (int j = 0; j < numNodes; ++j)
            for (int k = 0; k < numNodes; ++k)
                result[i][j] = result[i][j] | (A[i][k] & B[k][j]);
    
    return result;
}

// Method 1: Reachability using Boolean Matrix Multiplication
vector<vector<int>> computeReachabilityByMultiplication(vector<vector<int>> &adjMatrix) {

    int numNodes = adjMatrix.size();
    vector<vector<int>> R = adjMatrix; //A
    vector<vector<int>> power = adjMatrix; //A, Used to compute A^2, A^3, ..., A^n

    for (int step = 2; step <= numNodes; ++step) {
        
    // This loop computes A(2), A(3), ..., A(n) (Boolean powers).
        power = booleanMultiply(power, adjMatrix);

    // Combines all powers with logical OR ( ∨ ) to get the final reachability matrix. 
    // R = A v A(2) v A(3) v A(4)
        for (int i = 0; i < numNodes; ++i)
            for (int j = 0; j < numNodes; ++j)
                R[i][j] = R[i][j] | power[i][j];
    }
    return R;
}

// Method 2: Reachability using Warshall's Algorithm
vector<vector<int>> computeReachabilityByWarshall(vector<vector<int>> &adjMatrix) {

    int numNodes = adjMatrix.size();
    vector<vector<int>> R = adjMatrix; // A
    
    /* For each k = 0 to n-1:
     If R[i][k] == 0: Keep row i the same (no update needed).
     If R[i][k] == 1: Set row i = row i OR row k.*/
    for (int k = 0; k < numNodes; ++k) {
        for (int i = 0; i < numNodes; ++i) {
            if (R[i][k] == 1) {
                for (int j = 0; j < numNodes; ++j) {
                    R[i][j] = R[i][j] | R[k][j];
                }
            }
            // else: if R[i][k] == 0, do nothing (row stays the same)
        }
    }

    return R;
}
