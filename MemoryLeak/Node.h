// Linkded List Node Class
// Memory Leak Team

#ifndef _NODE
#define _NODE

template<class ItemType>
class Node
{
private:
    ItemType        item;
    Node<ItemType>* next;
    
public:
	Node()										{next = 0;}
	Node(const ItemType& anItem)				{item = anItem; next = 0; }
	void setItem(const ItemType& anItem)		{item = anItem;}
	void setNext(Node<ItemType>* nextNodePtr)	{next = nextNodePtr;}
	ItemType getItem() const					{return item;}
	Node<ItemType>* getNext() const				{return next;}
};

#endif
