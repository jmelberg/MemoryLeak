//  Containing IO functions
//  IO.CPP
//  Team Memory Leak
//  Created by Yupin Hu


#include "IO.h"

//this function will insert object
void readIn(BinarySearchTree<Restaurant*> &item, HashedTable * &hashPtr)
{
   string restaurant, review, foodType, distance;
   ifstream infile;
   string fname;
   string blank;
   int count = 0;
   cout << "Please enter filename with extenstion: " <<endl;
   getline(cin,fname);
   infile.open(fname.c_str());
   
   while (!infile)
   {
       cout << "Error opening file, please enter filename with extension for file type: " << endl;
       getline(cin, fname);
       infile.open(fname.c_str());
   }
   
   while (!infile.eof())
   {
       getline(infile, blank); // store data to walk full file
       count++;
   }
      
   int arraySize = (count*1.97) - 1;
   
   hashPtr = new HashedTable(arraySize);
   infile.close();
   
   infile.open(fname.c_str());
   
   while (!infile.eof() && infile.peek() != 10)		//Prevent the blank in the file
   {
       getline(infile, restaurant, ',');
       getline(infile, foodType, ',');
       getline(infile, review, ',');
       getline(infile, distance);
       Restaurant* temp = new Restaurant(restaurant, foodType, review, distance); //Place into Dynamic Memory
	     
       if (hashPtr->insert(temp)) // Insert into Hashed Table
			item.insert(temp, compareValue); // Insert into BST
	   
   }

   infile.close();
   
}

//this function will create an output file
void output(Restaurant *data)
{
   string fname;
   ofstream outFile;
   outFile.open("copy.txt", ofstream::app);
  
   outFile << data-> getRestaurant() << ',';
   outFile << data-> getFoodType() << ',';
   outFile << data-> getReview() << ',';
   outFile << data-> getDistance() << endl;
   
  outFile.close();
}

void clearFile()
{
   ifstream infile;
   infile.open("copy.txt", std::ofstream::out | std::ofstream::trunc); // make sure there is no data present
   infile.close();
}

bool compareValue (Restaurant * operand1, Restaurant * operand2, string symbol)
{
	if (symbol == "<")
	{
		return *operand1 < *operand2;
	}
	else if (symbol == ">")
	{
		return *operand1 > *operand2;
	}
	else if (symbol == "==")
	{
		return *operand1 == *operand2;
	}
	
	cout << "Invalid comparison symbol (<,>, ==)" << endl;
	return false;
}

Restaurant* copyValue(Restaurant* copyItem)
{
	Restaurant *tempCopy = new Restaurant (*copyItem);
	
	return tempCopy;
}

void indentedTree (Restaurant * & anItem, int width)
{
	cout << right << setw(width + static_cast<int>(anItem->getRestaurant().size())) << setfill('-') << anItem->getRestaurant() << setfill (' ') << endl;
}

bool compareHeap (Restaurant * operand1, Restaurant * operand2, string symbol)
{
   if (symbol == "<")
   {
       return operand1->getNumSearch() < operand2->getNumSearch();
   }
   else if (symbol == ">")
   {
       return operand1->getNumSearch() > operand2->getNumSearch();
   }
   else if (symbol == "==")
   {
       return operand1->getNumSearch() == operand2->getNumSearch();
   }
   
   cout << "Invalid comparison symbol (<,>,==)" << endl;

   return false;
}

bool checkDuplicate (Restaurant * operand1, Restaurant * operand2)
{
   return *operand1 == *operand2;
}

void displayLinkedList (Restaurant * item)
{
   item->printAll();
   cout << endl;
}

bool checkError (string & input)
{
	bool validInput;

	if (input.empty())
	{
		cout << "Need a name for restaurant in order to work.\n";
		validInput = false;
	}

	if (!input.empty())
	{
		validInput = false;
		bool frontSpace = isspace(input[0]);
		bool backSpace = isspace(input[input.size() - 1]);

		for (unsigned int i = 0; i < input.size() && !validInput; i++)
		{
			if (isalnum(input[i]))
			{
				validInput = true;
			}
		}

		for (unsigned int i = 0; i < input.size() && validInput; i++)
		{
			while (frontSpace)
			{
				input.erase(0, 1);
				if (!isspace(input[0]))
					frontSpace = false;
			}

			while (backSpace)
			{
				input.erase(input.size() - 1, 1);
				if (!isspace(input[input.size() - 1]))
				backSpace = false;
			}
		}
		
		if (!validInput)
		{
			cout << "Name of restaurant cannot contain space (' ') only.\n" << endl;
		}
	}
	
	return validInput;
}