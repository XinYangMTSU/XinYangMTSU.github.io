#include<iostream>
using namespace std;

//function declaration
int S_recursive(int n);
//function declaration
int S_iterative(int n);

int main()
{
    int num = 0;
    cout << "Please enter your integer number: " << endl;
    cin >> num;
    cout << "Series by S_recursive: " << endl;
    for(int i = 1; i <= num; i++)
        cout << "S(" << i << ") = " << S_recursive(i) << endl;


    cout << "Series by S_iterative: " << endl;
    for(int i = 1; i <= num; i++)
        cout << "S(" << i << ") = " << S_iterative(i) << endl;

    return 0;
}

int S_recursive(int n)
{
    if(n == 1)
        return 1;
    else
        return S_recursive(n-1) + n;
}

int S_iterative(int n)
{
    int currentValue = 1;
    if(n == 1)
        return 1;
    else
    {
        for(int i = 2; i <= n; i++)
            currentValue = currentValue + i;
        return currentValue;
    }
}
