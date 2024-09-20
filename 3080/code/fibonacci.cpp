#include<iostream>
using namespace std;

int fibonacciUsingRecursion(int n);
int fibonacciUsingIteration(int n);

int main()
{	
	int num = 0;
	cout << "Please enter an integer number:" << endl;
	cin >> num;

	cout << "Fibonacci series of " << num << " using Recursion is : " 
	     << fibonacciUsingRecursion(num) << endl;

		
	cout << "Fibonacci series of " << num << " using Iteration is : " 
	     << fibonacciUsingIteration(num) << endl;

	return 0;
}

int fibonacciUsingRecursion(int n)
{
	if(n == 1)
		return 0;
    else if( n == 2)
        return 1;
    
	return  fibonacciUsingRecursion(n-1) + fibonacciUsingRecursion(n-2);
}

int fibonacciUsingIteration(int n)
{
	int a = 0, b = 1, c;
    
	if(n == 1)
		return a;
    else if( n == 2)
        return b;
    
	for(int i = 3; i <=n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}

	return b;
}
