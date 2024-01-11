#include<iostream>
using namespace std;

//calculate the factorial of a number
unsigned long long int findFact(int);

//calculate the permutation 
unsigned long long int findNpR(int, int);

//calculate the combination
unsigned long long int findNcR(int, int);

int main()
{
	int n, r;
       	unsigned long long int nPr, nCr;

	cout << "Enter the value of n:" << endl;
	cin >> n;
	cout << "Enter the value of r:" << endl;
	cin >> r;

	nPr = findNpR(n,r);
	nCr = findNcR(n,r);

	unsigned long long int x , y;

	cout << findFact(n) << endl;
	cout << findFact(n-r) << endl;
	cout << findFact(r) << endl;

	x = findFact(n);
	y = findFact(n-r);

	cout << x/y << endl;

	cout << "Permutation, P(n,r) = " << nPr << endl;
	cout << "Combination, C(n,r) = " << nCr << endl;

	return 0;
}

unsigned long long int findFact(int n)
{
	if( n <= 1)
		return 1;
	else
		return n*findFact(n-1);
}	

unsigned long long int findNpR(int n, int r)
{
	return findFact(n) / findFact(n-r);
}

unsigned long long int findNcR(int n, int r)
{
	return findFact(n) / (findFact(n-r) * findFact(r));
}
