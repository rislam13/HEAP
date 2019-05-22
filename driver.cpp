#include <iostream>
using namespace std;
#include "heap.h"


/* arrange values in array a in ascending order
param a: the array
param size: the length of array (# of element)
*/
void hs(int a[], int size)
{//	cout << "FF"<< endl;
	Heap<int> heapInt(a, size);
	cout << "Arranged by HeapSort: ";
	for (int i=size-1;i>=0;i--)
	{	a[i] = heapInt.RemoveRoot();	
		cout << a[i] << " ";
	}
	cout << endl;
}



int main()
{	
	int a =0, lenght =7;
	
	int arr[] = {10,20,15,12,40,25,18};
	Heap<int> heapA(arr, lenght);
	cout << "Original: " ;
	heapA.print();
	if (!heapA.IsHeap())
		cout <<"Something is wrong!\n";
	
	//Insert a new element, and test heap property
	heapA.Insert(15);
 	cout << "After inerting 15: ";
	heapA.print();

	if (!heapA.IsHeap())
		cout <<"Something is wrong!\n";


	heapA.Modify(1, 30);
	cout << "After modifying index 1 to 30: ";
	heapA.print();
	if (!heapA.IsHeap())
		cout <<"Something is wrong!\n";
	
	cout <<"Removing Root:" ;
	heapA.RemoveRoot();
	heapA.print();
	if (!heapA.IsHeap())
		cout <<"Something is wrong!\n";


	cout << "\n\n\nFor testing the heap\n\n";
	hs(arr, lenght);

	return 0;
}
