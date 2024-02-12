#include<iostream>
using namespace std;

int factorialUsingRecursion(int n);
int factorialUsingIteration(int n);

int main()
{	
	int num = 0;
	cout << "Please enter an integer number:" << endl;
	cin >> num;

	cout << "Factorial of " << num << " using Recursion is : " 
	     << factorialUsingRecursion(num) << endl;

		
	cout << "Factorial of " << num << " using Iteration is : " 
	     << factorialUsingIteration(num) << endl;

	return 0;
}

int factorialUsingRecursion(int n)
{
	if(n==0)
	   return 1;
	return n*factorialUsingRecursion(n-1);
}

int factorialUsingIteration(int n)
{
	int res = 1;
	for(int i = 2; i <=n; i++)
		res *= i;
	return res;
}
