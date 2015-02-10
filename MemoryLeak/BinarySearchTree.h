// Binary Search Tree ADT
// Name : VY NHAT NGUYEN LIEU

 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"


template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, bool visit (ItemType, ItemType, string));
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType & target, bool & success, bool visit (ItemType, ItemType, string));
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target, bool visit (ItemType, ItemType, string)) const;
   
public:  
	// insert a node at the correct location
    bool insert(ItemType & newEntry, bool visit (ItemType, ItemType, string));
	// remove a node if found
	bool remove(const ItemType & anEntry, bool visit (ItemType, ItemType, string));
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem, bool visit (ItemType, ItemType, string)) const;
 
};

///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(ItemType & newEntry, bool visit (ItemType, ItemType, string))
{
	BinaryNode<ItemType> * newNodePtr = new BinaryNode<ItemType> (newEntry);
	BinarySearchTree::rootPtr = _insert(BinarySearchTree::rootPtr, newNodePtr, visit);
	BinarySearchTree::count++;
	
	return true; 
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target, bool visit (ItemType, ItemType, string))
{
	bool isSuccessful = false;
	BinarySearchTree::rootPtr = _remove(BinarySearchTree::rootPtr, target, isSuccessful, visit);
	if (isSuccessful)
	{
		BinarySearchTree::count--;
	}

	return isSuccessful; 
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType & anEntry, ItemType & returnedItem, bool visit (ItemType, ItemType, string)) const
{
	BinaryNode<ItemType> * tempFind;
	tempFind = findNode(BinarySearchTree::rootPtr, anEntry, visit);
	if (tempFind)	
	{
		returnedItem = tempFind->getItem();
		return true;
	}
	
	return false;
}

//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr, bool visit (ItemType, ItemType, string))
{
	if (nodePtr != 0)
	{
		if (visit (nodePtr->getItem(), newNodePtr->getItem(), ">"))
		{
			nodePtr->setLeftPtr(_insert (nodePtr->getLeftPtr(), newNodePtr, visit));
		}
		else if (visit (nodePtr->getItem(), newNodePtr->getItem(), "<"))
		{
			nodePtr->setRightPtr(_insert (nodePtr->getRightPtr(), newNodePtr, visit));
		}
	}
	else
	{
		return newNodePtr;
	}

	return nodePtr;
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType & target, bool & success, bool visit (ItemType, ItemType, string))

{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}

	if (visit (nodePtr->getItem(), target, ">"))		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, visit));
	else if (visit (nodePtr->getItem(), target, "<"))	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, visit));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();

		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();

		delete nodePtr;

		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue = nodePtr->getItem();

		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		ItemType tempDelete = successor;
		successor = nodePtr->getItem();
		nodePtr->setItem(tempDelete);

		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target, bool visit (ItemType, ItemType, string)) const 
{
	if (nodePtr != 0)
	{
		if (visit (nodePtr->getItem(), target, "=="))
		{
			return nodePtr;
		}
		else if (visit (nodePtr->getItem(), target, "<"))
		{
			return findNode (nodePtr->getRightPtr(), target, visit);
		}
		else
		{
			return findNode (nodePtr->getLeftPtr(), target, visit);
		}
	}
	else
	{
		return 0;
	}
}  

#endif
