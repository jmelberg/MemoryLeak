// Binary tree abstract base class
// Name : VY NHAT NGUYEN LIEU
// Date: 6/17/14
// Creates Binary Tree
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include <vector>
#include <string>
using namespace std;

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree()											{rootPtr = 0; count = 0;}		//Default constructor
	BinaryTree(const BinaryTree<ItemType> & tree, ItemType visit (ItemType))		{rootPtr = _copyTree(tree.rootPtr, visit); count = tree.count;}		//Copy constructor which just do shallow copy
	virtual ~BinaryTree()									{clear();}		//Destructor
	BinaryTree & operator=(const BinaryTree & sourceTree);		//Operator ==
   
	// common functions for all binary trees
 	bool isEmpty() const				{return count == 0;}	// Checks if input is empty
	int size() const					{return count;}			// Size of the tree
	void clear()						{destroyTree(rootPtr); rootPtr = 0; count = 0;}		// Clear the whole tree

	// Function to travel the tree.
	void preOrder(void visit(ItemType &)) const							{_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const							{_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const						{_postorder(visit, rootPtr);}
	void RNLOrder(void visit(ItemType &)) const							{_RNLorder(visit, rootPtr);}	// For cout the reverse alphabetical order.
	void RNLOrder (void visit(ItemType &, int), int & width) const		{_RNLorder(visit, rootPtr, width);}	// For print indented tree.
	
	// Function to delete backup (it is not general, but it is specific for our project)
	void deleteBackup ()												{count = 0; rootPtr = 0;}
	
	//function do the deep copy
	void copyTree (const BinaryTree<ItemType> & copyItem, vector <ItemType> &arr, ItemType visit (ItemType))	{clear(); rootPtr = _copyTree (copyItem.rootPtr, arr, visit); count = copyItem.count;}

	// abstract functions to be implemented by derived class
	virtual bool insert(ItemType & newData, bool visit (ItemType, ItemType, string)) = 0; 
	virtual bool remove(const ItemType & data, bool visit (ItemType, ItemType, string)) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem, bool visit (ItemType, ItemType, string)) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* _copyTree(const BinaryNode<ItemType>* nodePtr, vector <ItemType> &arr, ItemType visit (ItemType));

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _RNLorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _RNLorder (void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int & width) const;
   
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::_copyTree(const BinaryNode<ItemType>* nodePtr, vector <ItemType> &arr, ItemType visit (ItemType)) 
{
	BinaryNode<ItemType>* newNodePtr = 0;

	if (nodePtr != 0)
	{
		ItemType tempCopy = visit (nodePtr->getItem());
		arr.push_back (tempCopy);
		newNodePtr = new BinaryNode<ItemType> (tempCopy);
		newNodePtr->setLeftPtr(_copyTree (nodePtr->getLeftPtr(), arr, visit));
		newNodePtr->setRightPtr(_copyTree (nodePtr->getRightPtr(), arr, visit));
	}
   
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree (nodePtr->getLeftPtr());
		destroyTree (nodePtr->getRightPtr());
		delete nodePtr;

	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}

template <class ItemType>
void BinaryTree<ItemType>::_RNLorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const	// For reverse alphabetical order.
{
	if (nodePtr != 0)
	{
		_RNLorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_RNLorder(visit, nodePtr->getLeftPtr());
	}
}

template <class ItemType>
void BinaryTree<ItemType>::_RNLorder (void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int & width) const
{
	if (nodePtr != 0)
	{
		width += 4;
		_RNLorder(visit, nodePtr->getRightPtr(), width);
		ItemType item = nodePtr->getItem();
		visit(item, width);
		_RNLorder(visit, nodePtr->getLeftPtr(), width);
		width -= 4;
	}
}

template <class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	clear ();		// Delete the tree before making copy.
	rootPtr = sourceTree.rootPtr;//_copyTree (sourceTree.rootPtr, copyValue);
	count = sourceTree.count;

    return *this;
}

#endif