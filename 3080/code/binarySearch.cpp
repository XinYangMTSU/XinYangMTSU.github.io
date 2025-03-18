#include<iostream>
using namespace std;

int BinarySearch(int a[], int aSize, int toFind);
 
int main()
{
	int list[12] = {-2,1,2,3,5,7,8,10,14,15,38,61};
	int toFind = 14;
	int index = BinarySearch(list,12,toFind);
	
	if(index != -1)
		cout << toFind << " is found at position " << index << endl;
	else
		cout << toFind << " is not found in the list. " << endl;

	return 0;
}


int BinarySearch(int a[], int aSize, int toFind)
{
    int start = 0;                         //the search starts with index 0
    int last = aSize -1;                   //last is the last array index
	int middle = 0;

	cout << "start " << start << endl;
	cout << "last " << last << endl; 
 
    while (start <= last)                  //while there is still a place to look.      
    {
         middle = (start + last) / 2;  //Look here first
		 cout << "middle: " << middle << endl;
         if (toFind == a[middle])          //Found item. Quit. 
               return middle;
         else if (toFind > a[middle])           //Look in the last half
               start = middle + 1;
         else                              //OR look in the first half
               last =  middle - 1;
    }
    //the element wasn't found
    return -1;
}
