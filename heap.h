
 /*Name:Reham Islam
    * Professor Zhang
    * This is a heap class for Lab 2
   */
  
#include<iostream>
#include <cassert>
using namespace std;
 
const int MAX_SIZE = 20;
#ifndef HEAP_H
#define HEAP_H
template <class T>

class Heap{

public:
    	Heap<T>();
	Heap(T initData[], int len);

    	void heapify(int i);    
	void Modify(int position, T  value );

       // remove and return item stored in root from the heap
    	T RemoveRoot();

   	// return the item stored in the root node of the heap
   	T  GetRoot();

	void Insert(T item);

        //prints out all of the content of the data
    	void print();
    

	//return true if heap property is satisfied, false if violated 
    	bool IsHeap();




private:

     int parent(int i);
     void build_heap();

     // if node i has no left child, return -1 (note use heapLength to see if there is one)
     int leftchild (int i);

     //return the numbering of the right child of node i
     // if node i has no right child, return -1 (note use heapLength to see if there is one)
     int rightchild (int i);

     T data[MAX_SIZE];  //You could store elements from index 1 (i.e., leave
     	//first slot of the array empty), this way, you can use the above parent(),leftchild(), 
	//rightchild() functions to return the location of the these nodes
     int heapLength;   // the actual number of elements in the heap 
};

template <typename T>
Heap<T>::Heap()
{	heapLength = 0;
}

//Initialize the heap with the given data, and call build_heap to make it a heap
template <typename T>
Heap<T>::Heap(T initData[], int len)
{	for(int i =0; i < len; i++)
	{	data[i] = initData[i];
	}
	
	heapLength = len;
	build_heap();
	cout << "Heapify: ";
	print();
	assert (IsHeap());	
}


/* precondition:
  *   1) heapLength>=i>1
  *   2) node i's left subtree and right subtree meet the heap property, 
  *   node i might violate heap property, 
  * postcondition: the subtree rooted at node i met heap property */

template <typename T>
void Heap<T>::heapify(int i)
{	int l = i;
	int lc = leftchild(i);
	int rc = rightchild(i);

	//cout << "Heapify" << endl;
	//finding the largest value from the rott by checking the child
	if (lc <= heapLength && data[lc] > data[i] && leftchild(i) != -1) 
		l = lc; 
	else 
		l = i;
	if (rc <= heapLength && data[rc] > data[l] && rightchild(i) != -1) 
		l = rc; 
	
	//if the largest doesnt equal to root then the swap happend and heapify continues
	if (l != i) 
	{ 	swap(data[i], data[l]); 
		if(leftchild(i) != -1 || rightchild(i) != -1)
			heapify(l);
	} 

}


/*  modify item stored in position i to the newValue, and repair heap property.
      *   Precondition: heap property is statisfied, 
      *   	        1<=i<=length
      *   Postcondition: i-th element is modified, and heap property is satisfied 
      *   Note that you cannot just call build_heap, which is overkill, instead you 
      *   need to repair heap property as efficient as possible).
     When node i's value is changed to a smaller value, then heapify(i) can fix the whole heap.
     When node i's value is changed to a larger value, then the tree rooted at i is still a heap, 
       but the whole tree might not. THink about how to fix! 
      */   
template <typename T>
void Heap<T>::Modify(int position, T  value )
{	
	if (value >= data[position] && value <= data[parent(position)] )
	{	//correct position no movement needed
		data[position] = value;
		//cout<< "first"<< endl;
	} else if (value <= data[position] && (value > data[leftchild(position)] || value > data[rightchild(position)] ))
	{	//the data when is less than the parent. heapify is done until fixed
		data[position] = value;
		for(int i = position/2+1; i>=0; i--)
			heapify(i);	
		//cout << "second" << endl;	
	}else if(value > data[position] && value > data[parent(position)])
	{	//the value  when is lower than the parent. it checks and swaps wit the child to make sure it is heap
		int temp = position;
		data[position] = value;
		while(data[temp] > data[parent(temp)] && temp >= 0)
 	        {       
			swap(data[temp], data[parent(temp)]);
        	        temp = parent(temp);
          	}
	//	cout << "thrid"<<endl;
	}
}


 // remove and return item stored in root from the heap
template <typename T>
T Heap<T>::RemoveRoot(){
	T rootElement=data[0];
	// swap last with root
	swap(data[heapLength-1], data[0]);

	// decrease length,
	heapLength--;
	//print();
	// heapify from root
	for(int i = (heapLength/2)-1; i >=0; i--)
	{	//cout << "RR: " << i << endl;
		heapify(i);
	}

	return rootElement;
}


   // return the item stored in the root node of the heap

template <typename T>
T  Heap<T>::GetRoot()
{    return data[0];
}

/* insert a new item into the heap. 
     * Precondition: length+1<MAX_SIZE; //We have room to grow 
	1. increment heap length by 1
	2. store new item at the end of the heap, say the location is j
	3. walk your way up from node j to root (going one level up to parent in each step,
		compare values stored at a node with its parent and swap
	  the items if necessary.
	  */
template <typename T>
void Heap<T>::Insert(T item)
{	//this fuctions works when the previous elemts are sorted as heap
	if(heapLength+1 <= MAX_SIZE && IsHeap())
	{
		int temp = heapLength;
		data[heapLength] = item;
		heapLength++;

		//This loop basically checks whether the inserted value is placed into right spot
		//It loops from the insrted value and goes up checking with the parent
		while(data[temp] > data[parent(temp)] && temp != 0)
		{	swap(data[temp], data[parent(temp)]);
			temp = parent(temp);
		}
		
			
	}
 }







//prints out all of the content of the data
template <typename T>
 void Heap<T>::print()
 {	for(int i =0; i < heapLength; i++)
	{	cout << data[i] << " " ;
	}
	cout << endl;
 }

template <typename T>
 bool Heap<T>::IsHeap()
 {	bool t = true;
	for(int i =0; i < heapLength/2; i++) //from 0 to heapLenght/2,which means it checks all of the non leaf nodea
	{	if(data[i] < data[leftchild(i)] && leftchild(i) !=-1)
		{	t = false;
	//		cout << "I:" << i << endl;
			break;
		}
		if(data[i] < data[rightchild(i)]&& rightchild(i) !=-1)
		{	//cout << "rc: " << rightchild(i) << endl;
			t = false;
	//		cout << "i" << i << endl;
			break;
		}
	}
	return t;
 }


//precondition: i is the numbering of node (starting from 1)
//              i is not 1 (as root node has no parent)
//postcondition: the numbering of node i's parent is returned
template <typename T>
int Heap<T>::parent(int i)
{	return ((i-1)/2);
}


/* Precond: 
      the array has been filled with elements, but heap property is not satisfied
      Postcondition:  rearrange elements so that the whole heap statisfies heap property. 
      *This method should be called in the second constructor*/
template <typename T>
void Heap<T>::build_heap()
{		//int lenght = heapLength;	
		for (int i = heapLength/2-1; i >= 0 ; i--)
		{//	cout << "IBH: " << i << endl;
			heapify(i);
		//	cout << "F: " << i << endl;
		}
}


// if node i has no left child, return -1 (note use heapLength to see if there is one)
template <typename T>
int Heap<T>::leftchild (int i)
{	if(2*i+1 < heapLength)
		return(2*i+1);
	else
		return -1;
}

//return the numbering of the right child of node i
     // if node i has no right child, return -1 (note use heapLength to see if there is one)
template <typename T>
int Heap<T>::rightchild (int i)
{	if(2*i+2 < heapLength)
		return(2*i+2);
	else
		return -1;
}



#endif

