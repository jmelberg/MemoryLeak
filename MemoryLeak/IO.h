//  Containing IO functions header files
//  IO.h
//  Team Memory Leak
//  Created by Yupin Hu

#ifndef group_Standard_h
#define group_Standard_h

#include <iostream>
#include <string>
#include <fstream>
#include "HashedTable.h"
#include "BinarySearchTree.h"
#include "Restaurant.h"

void readIn(BinarySearchTree<Restaurant*> &item, HashedTable * &hashPtr);

void output(Restaurant*);
void clearFile();

bool compareValue (Restaurant * operand1, Restaurant * operand2, string symbol);

Restaurant* copyValue (Restaurant* copyItem);

void indentedTree (Restaurant * & anItem, int width);

bool compareHeap (Restaurant * operand1, Restaurant * operand2, string symbol);

bool checkDuplicate (Restaurant * operand1, Restaurant * operand2);

void displayLinkedList (Restaurant * item);

bool checkError (string & input);

#endif