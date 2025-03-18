#include<iostream>
using namespace std;

void bubbleSort(int array[],int aSize);
void printArray(int array[], int aSize);
void mySwap(int &a, int &b);

int main()
{
	int list[5] = {5, 1, 4, 2, 8};

	cout << "Before sorting: " << endl;
	printArray(list,5);
	bubbleSort(list,5);
	cout << "After sorting: " << endl;
	printArray(list,5);
	
	return 0;
}

void bubbleSort(int array[],int aSize)
{
   	for(int i = 0; i < aSize -1; i++)
	{
	   for(int j = 0; j < aSize-1-i; j++)
		if(array[j] > array[j+1])
		   mySwap(array[j], array[j+1]);
	}
}

void printArray(int array[], int aSize)
{
	for(int i = 0; i < aSize; i++)
	{
		cout << array[i]<< " ";
	}
	cout << endl;
}

void mySwap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}
