// Team: Memory Leak.
// Program: Heap ADT.
// Name: VY NHAT NGUYEN LIEU.
// Date: 06/12/2014.

#ifndef _HEAP_SEARCH
#define _HEAP_SEARCH

#include <string>
#include <vector>
using namespace std;

template <class ItemType>
class HeapMostSearch
{
private:
	int count;					// Total nodes
	int sizeArr;				// Size of the heapArr
	ItemType * heapArr;			// The heap array

	void heapCreate (int numElements, bool visit (ItemType, ItemType, string));			// Function creates the heap from the array
	void heapRebuild (int index, bool visit (ItemType, ItemType, string));				// Rebuild heap after delete
	void swap (int index1, int index2);													// Function swaps value in the heap array

public:
	// Default constructor
	HeapMostSearch ()																{count = 0; heapArr = 0; sizeArr = 0;}
	// Destructor
	~HeapMostSearch ()																{clear();}
	
	// General functions for Heap
	bool isEmpty () const															{return count == 0;}			// Check the heap is empty or not
	int getNumberOfNodes () const													{return count;}					// Return total nodes
	int getHeight () const															{return static_cast <int> (ceil((log(count + 1.0)/log(2.0))));}		// Return the height of the heap
	bool getTop (ItemType & returnItem) const											{if (isEmpty()) return false; returnItem = heapArr[0]; return true;}				// Return the value at the root
	bool add (ItemType & addNode, bool visit (ItemType, ItemType, string), bool visit1 (ItemType, ItemType));			// Add new value to the heap, and check for duplicate too						
	bool remove (bool visit (ItemType, ItemType, string));																// Remove root
	bool update (const ItemType & updateNode, bool visit (ItemType, ItemType, string), bool visit1 (ItemType, ItemType));	// Update heap after deleting data
	void clear ()																		{count = 0; sizeArr = 0; delete [] heapArr; heapArr = 0;}	// Clear out everything on the heapSearch
	void copy (const HeapMostSearch<ItemType> & copyHeap, const vector <ItemType> & arr, bool visit (ItemType, ItemType));			// Do the copy for backupHeap

	// Delete backup Heap (it is not general, but it is specified for our project)
	void deleteBackup ()																{count = 0; sizeArr = 0; heapArr = 0;}

};

template <class ItemType>
void HeapMostSearch<ItemType>::swap (int index1, int index2)
{
	ItemType temp = heapArr[index1];
	heapArr[index1] = heapArr[index2];
	heapArr[index2] = temp;
}

template <class ItemType>
void HeapMostSearch<ItemType>::heapCreate (int numElements, bool visit (ItemType, ItemType, string))
{
	for (int i = (numElements - 2) / 2; i >= 0; i--)
	{
		heapRebuild(i, visit);
	}
}

template <class ItemType>
void HeapMostSearch<ItemType>::heapRebuild (int index, bool visit (ItemType, ItemType, string))
{
	ItemType leftValue, rightValue;
	int largeIndex;
	
	if ((index * 2) + 1 < count)
	{
		leftValue = heapArr[(index * 2) + 1];
		if ((index * 2) + 2 > (count - 1))
		{
			largeIndex = (index * 2) + 1;
		}
		else
		{
			rightValue = heapArr[(index * 2) + 2];
			if (visit (leftValue, rightValue, ">"))
			{
				largeIndex = (index * 2) + 1;
			}
			else
			{
				largeIndex = (index * 2) + 2;
			}
		}
		if (visit (heapArr[index], heapArr[largeIndex], "<"))
		{
			swap (index, largeIndex);
			heapRebuild (largeIndex, visit);
		}
	}
}

template <class ItemType>
bool HeapMostSearch<ItemType>::add (ItemType & addNode, bool visit (ItemType, ItemType, string), bool visit1 (ItemType, ItemType))
{
	if (count == 0)
	{
		sizeArr = 10;
		heapArr = new ItemType [sizeArr];
		heapArr[count] = addNode;
		count++;
		return true;
	}
	
	if (count >= sizeArr)
	{
		double height = ceil((log(count + 1.0)/log(2.0)));
		int fullSize = static_cast <int> (pow(2, height)) - 1;
			
		ItemType * newHeap = heapArr;
		heapArr = new ItemType [fullSize];
		for (int i = 0; i < sizeArr; i ++)
		{
			heapArr[i] = newHeap[i];
		}
		sizeArr = fullSize;
			
		delete [] newHeap;
	}

	bool duplicate = false;
	int index = 0, duplicateIndex;

	while (index < count && !duplicate)
	{
		if (visit1 (heapArr[index], addNode))
		{
			duplicateIndex = index;
			duplicate = true;
		}
		index++;
	}

	if (duplicate)
	{
		heapArr[duplicateIndex] = addNode;
		heapCreate (count, visit);
		return true;
	}

	heapArr[count] = addNode;
	count++;
	heapCreate (count, visit);
	
	return true;
}



template <class ItemType>
bool HeapMostSearch<ItemType>::remove (bool visit (ItemType, ItemType, string))
{
	if (count == 0)
	{
		return false;
	}
	if (count == 1)
	{
		count--;
		return true;
	}
	swap (0, count - 1);
	count--;
	heapRebuild (0, visit);
	
	return true;
}

template <class ItemType>
bool HeapMostSearch<ItemType>::update (const ItemType & updateNode, bool visit (ItemType, ItemType, string), bool visit1 (ItemType, ItemType))
{
	bool same = false;
	int index = 0, sameIndex;

	while (index < count && !same)
	{
		if (visit1 (heapArr[index], updateNode))
		{
			sameIndex = index;
			same = true;
		}
		index++;
	}

	if (same)
	{
		heapArr[sameIndex] = heapArr[count - 1];
		count--;
		heapCreate (count, visit);
	}
	
	return true;
}

template <class ItemType>
void HeapMostSearch<ItemType>::copy (const HeapMostSearch<ItemType> & copyHeap, const vector <ItemType> & arr, bool visit (ItemType, ItemType))
{
	count = copyHeap.count;
	sizeArr = copyHeap.sizeArr;
	heapArr = new ItemType [sizeArr];
	
	bool found = false;

	for (int i = 0; i < copyHeap.count; i++)
	{
		for (unsigned int j = 0; j < arr.size() && !found; j++)
		{
			found = visit (copyHeap.heapArr[i], arr[j]);
			if (found)
			{
				heapArr[i] = arr[j];
			}
		}
	}
}

#endif