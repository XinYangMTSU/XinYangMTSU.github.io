#include<iostream>
using namespace std;

// A: n x m
// B: m x p
// A.B: n x p

int main()
{
 const int N = 2;
 const int M = 3;
 const int P = 2;

 int A[N][M] = {{2,4,3},
                {4,-1,2}};
 int B[M][P] = {{5,3},
                {2,2},
                {6,5}};
 int C[N][P] = {0};

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


    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < P; j++)
        {
            C[i][j] = 0;
            for(int k = 0; k < M; k++)
            {
                C[i][j] = C[i][j] + A[i][k]*B[k][j];
            }
        }
    }

    cout << "A.B = : " << endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < P; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }


    return 0;
}
