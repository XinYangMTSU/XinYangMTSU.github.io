#include<iostream>
using namespace std;

int LinearSearch (int a[], int aSize, int toFind);
 
int main()
{
	int list[12] = {3,15,2,8,7,1,14,38,10,-2,61,5};
	int toFind = 14;
	int index = LinearSearch(list,12,toFind);
	
	if(index != -1)
		cout << toFind << " is found at position " << index << endl;
	else
		cout << toFind << " is not found in the list. " << endl;

	return 0;
}

int LinearSearch (int a[], int aSize, int toFind) 
{ 
     // Look through all items, starting at the front. 
     for (int i = 0; i < aSize; i++)     
         if (a[i] == toFind)            
             return i; 
  
     // You've gone through the whole list without success.  
     return -1; 
}
