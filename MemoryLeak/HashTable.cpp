//
//  HashedTable.cpp
//  Team Project
//  Team Memory Leak
//  Created by Avi Rynderman on 5/25/14.
//  Copyright (c) 2014 Avi Rynderman. All rights reserved.
//

#include "HashedTable.h"
#include "HashTableNode.h"
#include "math.h"
using namespace std;


HashedTable::HashedTable(HashedTable* oldTable, const vector <Restaurant*> &array, int numOfRestaurants)
{
   this->size = oldTable->size; // Formula from readin in standard.
   this->numberOfRestaurants = numOfRestaurants;
   this->firstNode = new HashTableNode [this->size];
   
   for (int i = 0; i < size; i++)
   {
       // Set wasUsed in the new table with wasUsed in the old table
       this->firstNode[i].setWasUsed(oldTable->firstNode[i].hadBeenUsed());
       
       // Set the number of collisions in the node with its counterpart in the old table
       this->firstNode[i].collisionIncrease(oldTable->firstNode[i].getCollisions());
       
       // Check if node at element i of the old table has a pointer to info
       if (oldTable->firstNode[i].hadBeenUsed() && oldTable->firstNode[i].getItemPtr() != 0)
       {
           bool   found = false;
           int    counter = 0;
           string name = (oldTable->firstNode[i].getItemPtr())->getRestaurant();
           
           // Walk array for new pointer to same data
           while (found == false && counter < numOfRestaurants)
           {
               // Make sure pointer is not pointing to null
               if (array[counter] != 0)
               {
                   // Check for no equal
                   if (array[counter]->getRestaurant() != name)
                       counter++;
                   // If equal end the loop
                   else if (array[counter]->getRestaurant() == name)
                       break;
               }
           }
           
           // Insert into the correct location in the hash table
           if (array[counter]->getRestaurant() == name)
           {
               found = true;
               this->firstNode[i].setItemPtr(array[counter]);
           }
       }
   }
}

string HashedTable::stringToLower(string name)
{
    for (unsigned int i = 0; i<name.length(); i++)
        name[i] = tolower(name[i]);
    return name;
}

int HashedTable::collisionResolution(int index, string name)
{
    string temp;
    for (int i = 0; i< name.length(); i++)
    {
        temp += name[name.length() - i - 1];
    }
    index += hashingFunction(temp);
    return index;
}
bool HashedTable::insert(Restaurant *itemPtr)
{
    int numberColls = 0;
    if (numberOfRestaurants == size)
    {
        cout << "Too many items! Insert fail" << endl;
        return false;
    }
    if (itemPtr == 0)
        return false;
    string name = itemPtr->getRestaurant();
    int index = 0;
    index = hashingFunction(name);
    
    // Loop while the the index of the firstNode was used
    while (firstNode[index].hadBeenUsed() && firstNode[index].getItemPtr() != 0)
    {
        // Check if the restaurant at the current node is equal to the one trying to be inserted
        if (firstNode[index].getItemPtr()->getRestaurant() == itemPtr->getRestaurant())
        {
            cout << "Item already exists in the list. Insert will not happen to avoid duplicates: ";
            string temp= firstNode[index].getItemPtr()->getRestaurant();
            cout << temp << endl;
            return false;
        }
        index = (collisionResolution(index, itemPtr->getRestaurant())) % size;
        numberColls++;
    }

    // Insert
    firstNode[index].setItemPtr(itemPtr);
    firstNode[index].collisionIncrease(numberColls);
    
    numberOfRestaurants++;
	return true;
}

void HashedTable::display(void visit(Restaurant* ptr))
{
    for (int i = 0; i < size; i++)
    {
        if(firstNode[i].hadBeenUsed() && firstNode[i].getItemPtr() != 0)
        {
            visit(firstNode[i].getItemPtr());
        }
    }
}

void HashedTable::displayStats()
{
    // temp stores the number of collisions of a single restaurant
    int     temp = 0;
    int     maxColls = 0;
    string  restaurantsMaxColls;
    cout << "There are " << numberOfRestaurants << " restaurants in the directory" << endl;
    cout << "The size of the Hash Table is: " << size << endl;
    cout << "The load factor is " << fixed << setprecision(2) << (100.0*numberOfRestaurants / size) << "%\n" << endl;
    // Find words with most collisions
    for (int i = 0; i < size; i++)
    {
        if (firstNode[i].hadBeenUsed() && firstNode[i].getItemPtr() != 0)
        {
            temp = firstNode[i].getCollisions();
            // Base case for storing first item that has maxColls
            if (temp > maxColls && temp > 0)
            {
                maxColls = temp;
                restaurantsMaxColls.clear();
                // This line gets the name of the restuarant and store it in restaurantsMaxColls
                restaurantsMaxColls = (firstNode[i].getItemPtr())->getRestaurant();
                restaurantsMaxColls += ", ";
            }
            // Store more items that have same number of collisions
            else if (temp == maxColls && temp != 0)
            {
                // This line gets the name of the restuarant and appends it to restaurantsMaxColls
                restaurantsMaxColls += (firstNode[i].getItemPtr())->getRestaurant();
                restaurantsMaxColls += ", ";
            }
        }
    }
    if (maxColls > 0)
    {
        cout << "Max number of collisions is " << maxColls << " which occurs at restaurants: " << endl;
        cout << restaurantsMaxColls << endl;
        cout << endl << endl;
    }
}

bool HashedTable::findRestaurant(string name, Restaurant* & pointerToRestaurant)
{
    name = stringToLower(name);
    // Check if there is data in the hashTable
    if (numberOfRestaurants == 0)
        return false;
    bool found = false;
    int index = 0;
    index = hashingFunction(name);
    
    // Loop while the the the element at the current index is not equal to the name;
    // and while we haven't reached the end of a collision train
    while ((firstNode[index].hadBeenUsed()) && firstNode[index].getItemPtr() != 0 && (stringToLower((firstNode[index].getItemPtr())->getRestaurant()))  != name)
    {
        index = (collisionResolution(index, name)) % size;
    }
    
    // Now check if the element we are looking at is acutally equal to the name we want to find
    if ((firstNode[index].hadBeenUsed()) &&
        firstNode[index].getItemPtr() != 0 &&
        (stringToLower((firstNode[index].getItemPtr())->getRestaurant())) == name)
    {
        pointerToRestaurant = firstNode[index].getItemPtr();
        found = true;
        return found;
    }
    else
        return false;
}

bool HashedTable::deleteRestaurant(string name)
{
    // Check if there is data in the hashTable
    if (numberOfRestaurants == 0)
        return false;
    int index = 0;
    index = hashingFunction(name);
    
    while (firstNode[index].hadBeenUsed())
    {
        if (firstNode[index].getItemPtr() == 0)
            index = (collisionResolution(index, name)) % size;
        else if ((firstNode[index].getItemPtr())->getRestaurant() != name)
            index = (collisionResolution(index, name)) % size;
        else if ((firstNode[index].getItemPtr())->getRestaurant() == name)
        {
            firstNode[index].setItemPtr(0);
            firstNode[index].collisionIncrease(0);
            numberOfRestaurants--;
            return true;
        }
        else
            return false;
    }
    // Xcode doesn't like not having a return outside the loop
    return false;
}

bool HashedTable::deleteRestaurant (Restaurant* itemPtr)
{
    // Check if there is data in the hashTable
    if (numberOfRestaurants == 0)
        return false;
    int index = 0;
    index = hashingFunction(itemPtr->getRestaurant());
    
    // While not at the end of a collision train
    while (firstNode[index].hadBeenUsed())
    {
        // The first if makes sure the next couple lines don't call the functions of a aeroed pointer
        if (firstNode[index].getItemPtr() == 0)
            index = (collisionResolution(index, itemPtr->getRestaurant())) % size;
        else if (!(*(firstNode[index].getItemPtr()) == *itemPtr))
            index = (collisionResolution(index, itemPtr->getRestaurant())) % size;
        else if (*(firstNode[index].getItemPtr()) == *itemPtr)
        {
            firstNode[index].setItemPtr(0);
            firstNode[index].collisionIncrease(0);
            numberOfRestaurants--;
            return true;
        }
        else
            return false;
    }
    // Xcode doesn't like not having a return outside the loop
    return false;
}

// This hashing algorithm assigns an index to a word based on its components letters using a switch and while loop.
// The more common letters have smaller values, the less common get larger ones.
// Any clustering that comes from this function is random and unpredictable
// since a single letter difference between words would cause a substantial difference in index. For example the word
// "car" gets an index of 651 while "cat" gets 137.
// The larger/more exotic the word the farther spaced out the are.

// The numbr of probes reached a max of 4 and each word again displayed the functions ability to produce an
// unexpected, unpredictable index for each word.

int HashedTable::hashingFunction(string name)
{
    long int placement = 0;
    int i = 1;
    int a = i;

	
    name = stringToLower(name);
    while (i <= name.length())
    {
        // This if will guarantee placement never gets too long
        if (a > 6)
            a = 3;
        switch (name[i-1])
        {
            case('e'): placement += 1*pow(3.18,a);
                break;
            case('t'): placement += 2*pow(2.988,a);
                break;
            case('a'): placement += 3*pow(3.98,a);
                break;
            case('o'): placement += 4*pow(3.98,a);
                break;
            case('i'): placement += 5*pow(3.98,a);
                break;
            case('n'): placement += 6*pow(3.98,a);
                break;
            case('s'): placement += 7*pow(3.98,a);
                break;
            case('h'): placement += 8*pow(3.98,a);
                break;
            case('r'): placement += 9*pow(3.98,a);
                break;
            case('d'): placement += 10*pow(3.2128,a);
                break;
            case('l'): placement += 11*pow(3.2018,a);
                break;
            case('c'): placement += 12*pow(3.1008,a);
                break;
            case('u'): placement += 13*pow(3.338,a);
                break;
            case('m'): placement += 14*pow(3.328,a);
                break;
            case('w'): placement += 15*pow(3.318,a);
                break;
            case('f'): placement += 16*pow(3.308,a);
                break;
            case('g'): placement += 17*pow(3.208,a);
                break;
            case('y'): placement += 18*pow(3.808,a);
                break;
            case('p'): placement += 19*pow(3.48,a);
                break;
            case('b'): placement += 20*pow(2.8,a);
                break;
            case('v'): placement += 21*pow(3.98,a);
                break;
            case('k'): placement += 22*pow(3.08,a)*(i+0.324);
                break;
            case('j'): placement += 23*pow(3.9,a)*(i+0.334);
                break;
            case('x'): placement += 24*pow(3.48,a)*(i+0.344);
                break;
            case('q'): placement += 25*pow(3.18,a)*(i+0.354);
                break;
            case('z'): placement += 26*pow(3.28,a)*(i+0.364);
                break;
            default: placement += 31; 
        }
        placement = (placement%size);
        i++;
        a = i;
    }
	
    return static_cast<int>(placement);
}