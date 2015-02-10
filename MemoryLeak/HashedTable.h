//
//  HashedTable.h
//  Team Project
//  Team Memory Leak
//  Created by Avi Rynderman on 5/25/14.
//  Copyright (c) 2014 Avi Rynderman. All rights reserved.
//

#ifndef __CIS_22C_Code__HashedTable__
#define __CIS_22C_Code__HashedTable__

#include <iostream>
#include <iomanip>
#include "HashTableNode.h"
#include "Restaurant.h"
#include <vector>

using namespace std;

class HashedTable
{
private:
   // Data including the number of restaurants and the array
   int            size;
   int            numberOfRestaurants;
   HashTableNode* firstNode;
   
   // Hashing Function + collision resolution function
   int hashingFunction(string name);
   int collisionResolution(int index, string name);
   
public:
	//Default constructor
   HashedTable(int size) {this->size = size; firstNode = new HashTableNode [this->size]; numberOfRestaurants = 0;}
   
   // Constructor for backup. This accepts the old table, an array from the BST with all the new pointers,
   // and the size of the array (the number of the restaurants)
   HashedTable(HashedTable* oldTable, const vector <Restaurant*> &array, int numOfRestaurants);
   
   ~HashedTable()        {delete [] firstNode;}
   // Insert a restaurant into the hash table.
   // It requires a pointer to a restaurant object
   bool insert           (Restaurant* itemPtr);
   
   // Turn a string to lowercase string
   string stringToLower (string name);
   
   // Deleting from the hash table. This is overloaded so you can pass in whatever you want.
   // The boolean will return wether or not the delete was successful. It does the check.
   bool deleteRestaurant (string Restaurant);
   bool deleteRestaurant (Restaurant* itemPtr);
   
   // This function gets a visit function passed in. The function itself loops throught the data and
   // "visits" the data at that node.
   void display(void visit(Restaurant* ptr));
   
   // Finds a restaurant string in the hashTable. Must have name of restaurant and a pointer to be set (for accessing data)
   bool findRestaurant (string Restaurant, class Restaurant* & returnPointerToRestaurant);
   
   void displayStats();
};

#endif