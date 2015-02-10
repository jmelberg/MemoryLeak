// Program: DataRecord
// Name: Inderjit Bassi
// Date: 6/3/14
// This class creates the BST and HashedTabe

#ifndef  DATARECORD_H_INCLUDED
#define DATARECORD_H_INCLUDED

#include "BinarySearchTree.h"
#include "List.h"
#include "Restaurant.h"
#include "HashedTable.h"
#include "IO.h"
#include <cctype>
#include <vector>
#include "HeapMostSearch.h"

class DataRecord
{
private:
    int count;                           // Holds the count
    BinarySearchTree<Restaurant*> item;   // Private member data to the BST
    HashedTable *hashPtr;                // Private member data that creates a pointer to a hashedTabe
	HeapMostSearch<Restaurant*> heapSearch;

	int backupCount;                           // Holds the backup count
    BinarySearchTree<Restaurant*> backupItem;   // Private member data to the backup BST
    HashedTable * backupHashPtr;                // Private member data that creates a pointer to a backup hashedTabe
	HeapMostSearch<Restaurant*> backupHeapSearch;
    
protected:
	static Restaurant * copyValue (Restaurant * copyItem);				// Copies values for BST

public:
    DataRecord(); // default constructor
    ~DataRecord() {delete hashPtr; delete backupHashPtr;}
    
    // Display Functions
    static void printFull(Restaurant& sample) {sample.printAll(); cout << endl;}	// Prints out everything
    static void print(Restaurant * & sample) {sample->printKey();}					// Prints out the key (name)
    static void visit(Restaurant* ptr) {cout << ptr->getRestaurant() << endl;}      // Prints out the restaurant name
    static void copy(Restaurant*ptr, HashedTable* hashPtr);							// Copy 
    
    void add(string input, string type, string rating, string miles);	// Adds into BST and HashedTable
    void deleteData(string input);										// Delete function
    bool search(string input);											// Search function (HashedTable)
    void hashList() const {hashPtr->display(visit); cout << endl;}		// Displays the HashedTable
    void bstKey() const {item.inOrder(print); cout << endl;}			// Prints out the BST data in order
    void hashStats() const {hashPtr->displayStats(); cout << endl;}		// Prints out the Hash Statistics
    void backUp();														// Back up for BST and HashedTable
	void useBackup ();													// Uses the Back up for BST and HashedTable
    void compare();														// Compare function 
    void mostSearched(int num);											// HONORS: Shows the most searched for items
    bool save();														// Saves to output file
	void printTree()		{int width = 0; item.RNLOrder (indentedTree, width);}	// Prints out the indented tree

};

#endif  // DATA_H_INCLUDED
