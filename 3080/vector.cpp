#include <iostream>
#include <vector>//A std::vector in C++ is a dynamically resizable array provided by the C++ Standard Library
using namespace std;

//function prototype
void displayMatrix(const vector<vector<int>>& matrix);
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, 
                                   const vector<vector<int>>& B);

int main() {
    // Define matrix A (2 x 3)
    vector<vector<int>> A = {
        {2, 4, 3},
        {4, -1, 2}
    };

    // Define matrix B (3 x 2)
    vector<vector<int>> B = {
        {5, 3},
        {2, 2},
        {6, 5}
    };

    cout << "Matrix A:" << endl;
    displayMatrix(A);

    cout << "Matrix B:" << endl;
    displayMatrix(B);

    // Multiply A x B, store the result in C
    vector<vector<int>> C = matrixMultiply(A, B);

    cout << "Matrix C = A x B:" << endl;
    displayMatrix(C);

    return 0;
}

// Display a 2D vector (matrix).
void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val: row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "==========" << endl;
}

// Multiply two matrices A and B, stored in 2D vectors.
// A is size (N x M), B is size (M x P), result is (N x P).
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, 
                                   const vector<vector<int>>& B) 
{
    // Assume dimensions are compatible: A's columns = B's rows.
    int N = A.size();           // Number of rows in A
    int M = A[0].size();           // Number of columns in A
    int P = B[0].size(); // Number of columns in B
    
    // Prepare the result matrix C, size (N x P), initialized to 0.
    vector<vector<int>> C(N, vector<int>(P, 0));
    
    // Standard triple-nested loop for matrix multiplication.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < M; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}