// Team Project: Memory Leak
// Name: Inderjit Bassi
// Date: 6/16/14
// .cpp file for DataRecord

//note: take care in main check error

#include "DataRecord.h"
#include <iostream>
using namespace std;

Restaurant * DataRecord :: copyValue (Restaurant * copyItem)
{
	Restaurant * tempCopy = new Restaurant (*copyItem);
	return tempCopy;
}

DataRecord:: DataRecord()
{
	backupCount = 0;
	backupHashPtr = 0;
	hashPtr = 0;
    readIn(item, hashPtr); // Read in Data
    count = item.size();
}

void DataRecord:: add(string input, string type, string rating, string miles)
{
    Restaurant* temp = new Restaurant(input, type, rating, miles);
    item.insert(temp, compareValue); // Add to BST
    hashPtr->insert(temp); // Add to Hash
}

void DataRecord:: deleteData(string input)
{
    cout << "You are in the deleteData function of DataRecord" << endl;
    bool success = false;
	Restaurant * deleteItem = new Restaurant (input, "unknown", "unknown", "unknown");

	heapSearch.update (deleteItem, compareHeap, checkDuplicate); 

	success = item.remove(deleteItem, compareValue); // Already calls search function in BST
    
    if(success == true)
    {
        cout << input << " was deleted from BST." << endl;
    }
    else
        cout << input << " is not found in the BST." << endl;
    
    success = hashPtr->deleteRestaurant(deleteItem);

    if(success == true)
    {
        cout << input << " was deleted from HashTable." << endl;
    }
    else
        cout << input << " is not found in HashTable." << endl;
}

bool DataRecord::search(string input)
{
    bool found = false;
    Restaurant* returnedItem; // pointer for returnedItem
    
    found = hashPtr->findRestaurant(input, returnedItem);
    if(found==false)
    {
		cout << input << " is not found among these restaurants: " << endl;
		item.inOrder(print); // Used to print in order
		cout <<endl;
    }
	else
	{
		returnedItem->updateSearch();
		heapSearch.add(returnedItem, compareHeap, checkDuplicate);
		cout << endl;
		returnedItem->printAll();
		cout << endl;
	}    

    return found;
}

void DataRecord:: backUp()
{
	if (!(hashPtr == backupHashPtr || backupHashPtr == 0))				// In case the user presses backup multiple times, but not presses use backup.
	{
		backupItem.clear();
		backupCount = 0;
		backupHeapSearch.clear();
		delete backupHashPtr;
		backupHashPtr = 0;
	}

	backupCount = count;
	vector <Restaurant*> arrayTree;

	backupItem.copyTree (item, arrayTree, copyValue);

    backupHashPtr = new HashedTable (hashPtr, arrayTree, count);

	backupHeapSearch.copy(heapSearch, arrayTree, checkDuplicate);
	
}

void DataRecord::useBackup ()
{
	count = backupCount;
	item.clear();
	delete hashPtr;
	hashPtr = 0;
	heapSearch.clear();

	item = backupItem;
	hashPtr = backupHashPtr;
	heapSearch = backupHeapSearch;

	backupHeapSearch.deleteBackup();
	backupItem.deleteBackup();
	backupHashPtr = 0;
}

void DataRecord:: compare()
{
    string data;
    string choice1, choice2, choice3, choice4;
    char loc;
	int location;
    char key = ' ';
    int i = 1;
	bool found = false;
	List<Restaurant*> compareList;
	Restaurant * compareRestaurant;
	bool validInput;
    
    cout << "What restaurants would you like to compare? "<< endl;
    
	do
	{
		cout << "\t First Restaurant: ";
		getline(cin, choice1);

		validInput = checkError(choice1);

		if (validInput)
		{
			found = hashPtr->findRestaurant(choice1, compareRestaurant);
			if(found)
			{
				compareList.insert (compareRestaurant, 1);
				i++;
			}
			if (!found)
			{
				bstKey();
			}
		}
	} while (!found || !validInput);
    
	do
	{
	   cout << "\t Second Restaurant: ";
		getline(cin, choice2);

		validInput = checkError(choice2);

		if (validInput)
		{

		found = hashPtr->findRestaurant(choice2, compareRestaurant);
		 if(found)
		 {
			 compareList.insert (compareRestaurant, 2);
			  i++;
		 }
		 if (!found)
		 {
			 bstKey();
		 }

		}
	} while (!found || !validInput);
    
    compareList.displayList (displayLinkedList);

    while (key != 'e')
    {
		if (i <= 4)
		{
	        cout << "\t a. Compare another restaurant"<< endl;
		}
		cout << "\t p. Put restarants together" << endl;
		cout << "\t e. Exit to Menu Chocies" << endl;
        cout << "Choice: ";
        cin >> key;
        key = tolower(key);
        cin.ignore(100,'\n');

        if (key=='a' && i <= 4)
        {
			do
			{
                cout << "\t Next Restaurant: ";
                getline(cin, choice3);
				do
				{
					cout << "\t Location: ";
					cin >> loc;
					cin.ignore(100, '\n');
					if (!isdigit(loc))
					{
						cout << "\t Input has to be a number" << endl;
					}
				} while(!isdigit(loc));

                found = hashPtr->findRestaurant(choice3, compareRestaurant);
				if (!found)
				 {
					bstKey();
				 }
			}while (!found);
			
			if(found)
			{
				char * temp = &loc;
				if (atoi(temp) > i)
				{
					location = i;
				}
				else
				{
					
					location = atoi(temp);
				}

				 compareList.insert (compareRestaurant, location);
				i++;
			}
			compareList.displayList (displayLinkedList);
		} 
		else if (key == 'p')
		{
			char location1, location2;
			char * temp;
			
			do
			{
				cout << "\t Location: ";
				cin >> location1;
				cin.ignore(100, '\n');
				if (!isdigit(location1))
				{
					cout << "\t Input has to be a number" << endl;
				}
				else
				{
					temp = &location1;
					if (atoi(temp) > i)
					{
						cout << "\t Input has to be in between the number of restaurant\n";
					}
				}
			} while(!isdigit(location1) || (atoi(temp) > i));
			do
			{
				cout << "\t and: ";
				cin >> location2;
				cin.ignore(100, '\n');
				if (!isdigit(location2))
				{
					cout << "\t Input has to be a number" << endl;
				}
				else
				{
					temp = &location2;
					if (atoi(temp) > i)
					{
						cout << "\t Input has to be in between the number of restaurant\n";
					}
				}
			} while(!isdigit(location2) || (atoi(temp) > i));
			
			char * tempLocation1 = &location1;
			char * tempLocation2 = &location2;
			Restaurant * holdValue1;
			Restaurant * holdValue2;
			compareList.getEntry(atoi(tempLocation1), holdValue1);
			compareList.getEntry(atoi(tempLocation2), holdValue2);

			compareList.remove(atoi(tempLocation1));
			compareList.remove(atoi(tempLocation2) - 1);

			compareList.insert(holdValue1, 1);
			compareList.insert(holdValue2, 2);
				
			

			compareList.displayList(displayLinkedList);
		}
		else if (key == 'e')
		{
			cout << "\t Exit compare option\n";
		}
		else
		{
			cout << "\t Invalid input\n";
		}
	}

}

void DataRecord:: mostSearched(int num)
{
	if (heapSearch.isEmpty())
	{
		cout << "There is no restaurant which is searched" << endl;
		return;
	}
   
	Restaurant * tempArr [10];
	Restaurant * hold;
	int check = num;
	
	if (heapSearch.getNumberOfNodes() < num)
	{
		check = heapSearch.getNumberOfNodes();
		cout << "The number of restaurants that have been searched up to now is less than your resquest" << endl;
	}

	cout << endl;

    for (int i = 0; i < check; i++)
	{
		heapSearch.getTop (hold);
		tempArr[i] = hold;
		heapSearch.remove (compareHeap);
		
		cout << "Number " << i + 1 << endl; 
		tempArr[i]->printAll();
		cout << endl;
	}
	cout << endl;
	while (check < 10 && heapSearch.getTop(hold) && tempArr[check - 1]->getNumSearch() == hold->getNumSearch())
	{
		tempArr[check] = hold;
		cout << "Number " << check + 1 << endl;
		tempArr[check]->printAll();
		cout << endl;
		heapSearch.remove(compareHeap);
		check++;
	}

	for (int i = 0; i < check; i++)
	{
		heapSearch.add (tempArr[i], compareHeap, checkDuplicate);
	}
}

bool DataRecord:: save()
{
   bool save = true;
   clearFile(); //Clears .txt file for output
   hashPtr->display(output);
   cout << "Data Saved!" << endl;
   return save;
}
