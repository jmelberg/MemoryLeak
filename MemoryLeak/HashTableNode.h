//
//  HashTableNode.h
//  Team Project
//  Team Memory Leak
//  Created by Avi Rynderman on 5/25/14.
//  Copyright (c) 2014 Avi Rynderman. All rights reserved.
//

#ifndef Team_Project_HashTableNode_h
#define Team_Project_HashTableNode_h

#include <iostream>
#include "Restaurant.h"
#include "math.h"

using namespace std;

class HashTableNode
{
private:
   Restaurant* itemPtr;
   bool        wasUsed;
   int         numberOfCollisions;
public:
   HashTableNode()                  { itemPtr = 0; wasUsed = false; numberOfCollisions = 0; }
   ~HashTableNode()                 { if (itemPtr != 0) delete itemPtr; }
   void setWasUsed(bool value)      { wasUsed = value; }
   void setItemPtr(Restaurant* ptr) { itemPtr = ptr; wasUsed = true; }
   void deleteNode()                { if (itemPtr) delete itemPtr; itemPtr = 0; wasUsed = true; }
   void displayNode()               { cout << itemPtr->getRestaurant() << " " << itemPtr->getDistance() << endl; }
   void collisionIncrease(int num)  { numberOfCollisions = num; }
   int  getCollisions()             { return numberOfCollisions; }
   Restaurant* getItemPtr ()        { return itemPtr; }
   bool        hadBeenUsed ()       { return wasUsed; }
};


#endif