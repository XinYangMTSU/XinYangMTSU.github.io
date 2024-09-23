#include<iostream>
using namespace std;

// A: n x m
// B: m x p
// A.B: n x p

int main()
{

 // Matrix Dimensions
 
 const int N = 2;
 const int M = 3;
 const int P = 2;

 // Matrix Initialization
 int A[N][M] = {{2,4,3},
                {4,-1,2}};
 int B[M][P] = {{5,3},
                {2,2},
                {6,5}};
 int C[N][P] = {0};

 //  Printing Matrices in a readable format 
 
    cout << "A = : " << endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    cout << "==================" << endl;

    cout << "B = : " << endl;
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < P; j++)
            cout << B[i][j] << " ";
        cout << endl;
    }
    cout << "==================" << endl;

   // Matrix Multiplication

 //The outer loops i and j iterate over the elements of the result matrix C, where i represents the row index and j represents the column index.
 
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < P; j++)
        {
            C[i][j] = 0;
            // For each element C[i][j], the innermost loop (with index k) computes the dot product between the i-th row of A and the j-th column of B.
            for(int k = 0; k < M; k++)
            {
               //This is the core of matrix multiplication: C[i][j] is the sum of the products of corresponding elements in the i-th row of A and the j-th column of B.
                C[i][j] = C[i][j] + A[i][k]*B[k][j];
            }
        }
    }


    // Printing the Result
    cout << "A.B = : " << endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < P; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }


    return 0;
}
