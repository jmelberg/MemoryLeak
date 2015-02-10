// Linked List Header File
// Memory Leak Team


// Header and implementation for linked list with template
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
using namespace std;

template <class T>
class LinkedList
{
protected:
	
	Node<T> *headPtr;   // List head pointer
	int itemCount;

public:
	LinkedList() { headPtr = NULL; itemCount = 0; }
    ~LinkedList();
    
	// Linked list operations
	void insertNode(T);
	bool deleteNode(T);
	void displayList(void visit (T)) const;
};


/////////// Implementation portion of linked list with template  //////////////

// displayList: print all list data
template <class T>
void LinkedList<T>::displayList (void visit (T)) const
{
	Node<T> *ptr = headPtr;	// set pointer to begin of list
    
	while (ptr != NULL)      // walk to end of list
	{
		visit (ptr->getItem());		// print data of each node
		ptr = ptr->getNext();                // go to next node
	}
    cout << endl;
}

// insertNode: add a node in list order
template <class T>
void LinkedList<T>::insertNode(T newValue)
{
	Node<T> *newNode;
	Node<T> *pLoc;				// locate pointer
	Node<T> *pPre = NULL;		// previous pointer
    
	// Allocate a new node and store newValue
	newNode = new Node<T>();
	newNode->data = newValue;
	newNode->next = NULL;
    
	if (headPtr == NULL)    // insert first node
	{
        headPtr = newNode;
    }
	else				// insert in existing list
	{
		// walk to the correct location
		pLoc = headPtr;        // pLoc is at the begin of list
		pPre = NULL;		// pPre is null
		// walk until end of list or until current node data is larger than newNode data
		while (pLoc != NULL && pLoc->data < newValue)
		{
			pPre = pLoc;
			pLoc = pLoc->next;
		}
		
		// insert at correct location
		if (pPre == NULL)	// insert at begin of list
		{
			headPtr = newNode;
			newNode->next = pLoc;
		}
		else				// insert in middle or end of list
		{
			pPre->next = newNode;
			newNode->next = pLoc;
		}
	}
	itemCount++;
}

template <class T>
bool LinkedList<T>::deleteNode(T toBeDeleted)
{
	Node<T> *pLoc;			// locate pointer
	Node<T> *pPre;			// previous pointer
    
	if (!headPtr)		   // If the list is empty, done
		return false;
    
	// walk to find node to be deleted
    pLoc = headPtr;
	pPre = NULL;
	while (pLoc != NULL && pLoc->data < toBeDeleted)
    {
        pPre = pLoc;
        pLoc = pLoc->next;
	}
    
	// if found
	if (pLoc != NULL && pLoc->data == toBeDeleted)
    {
		itemCount--;
 		if (pPre)	// remove node at middle or end
			pPre->next = pLoc->next;	// link previous node with next node
		else		// remove node at beginning
			headPtr = pLoc->next;
        delete pLoc;				// release memory of pLoc
		return true;
    }
	return false;
}

// destructor, delete all nodes
template <class T>
LinkedList<T>::~LinkedList()
{
	Node<T> *ptr = headPtr;		// start at begin of list
	while (ptr != NULL)			// while not at end of list
	{
		headPtr = headPtr->getNext();		// find next node
		delete ptr;				// delete current node
		ptr = headPtr;				// set current node to next node
	}
}


#endif