//  main.cpp
//  Team Project
//  Team Memory Leak
//  Jordan Melberg

#include <iomanip>
#include <sstream>
#include "DataRecord.h"

using namespace std;

int main()
{
	DataRecord test; // Creates head node, BST, and HashTable through constructor.
	
	char key = ' ';
	string input, type, rating, miles;
    bool backup = false, save = true;
    
    while (key != 'q') // Loops until user wants to quit
    {
        cout    << "Main Menu" << endl
                << "\t a. Add New Data" << endl
                << "\t d. Delete Data" << endl
                << "\t f. Find and Display Data Using Primary Key"<< endl
                << "\t l. List Data" << endl
                << "\t p. Print Indented Tree" << endl
                << "\t h. Hash Statistics" << endl
                << "\t b. Backup" << endl;
        
		if (backup == true)
            cout << "\t u. Use Backup"<<endl;
        
        cout    << "\t c. Compare Data" << endl
                << "\t m. Most Searched (Honors)" << endl
                << "\t s. Save" << endl
                << "\t q. Quit" << endl << endl;
        
        cout << "Choice: ";
        cin >> key; // Only grabs the first character of input.
        key = tolower(key); // Convert to lower case
        
		// temp solution.
		cin.ignore (100, '\n');


        if (key == 'a') // Add New Data
        {

			bool validInput = true;

            cout << "Enter new restaurant: ";

            getline(cin, input);

			validInput = checkError(input);
           
			if (validInput && test.search(input) == false)
            {
                // As it is set up, it does not account for blank entries. We can change this if we'd like to
                cout << "Please enter type of food: ";
                //cin.ignore(100, '\n');
                getline(cin, type);
                cout << "Please enter rating (1 - 5) With 5/5 being a perfect score: ";
                //cin.ignore(100, '\n');
                getline(cin, rating);
                cout << "Please enter distance from De Anza (in miles): ";
                //cin.ignore(100, '\n');
                getline(cin, miles);

                test.add(input, type, rating, miles);	
				save = false;
			}
            else if (validInput)
                cout << "Already exists" << endl;
        }
        else if (key == 'd') // Delete Data
        {

            cout << "Enter restaurant to be deleted: ";
            getline(cin, input);

			bool validInput;
			validInput = checkError(input);
            
            if (validInput && test.search(input) == true)////////////////////////////---------------------------Do we need to search?? because delete will check if data exists or not.
			{
				save = false;
				test.deleteData(input);
			}
            else
                cout << "Does not exist" << endl;
        }
        else if (key == 'f') // Find Data
        {
            cout << "Enter restaurant to be found: ";
            getline(cin, input);

			bool validInput;

			validInput = checkError(input);
            
            if(validInput && test.search(input) == false)
				cout << input << " is not found in the list" << endl;
        }
        else if(key == 'l')
        {
            cout	<< "\t h. Hash Table Data" << endl
					<< "\t b. BST Sorted Order"<<endl;
            cout << "Choice: ";
            cin >> key; // Only grabs the first character of input.
            key = tolower(key);

			cin.ignore (100, '\n');
            
            if (key == 'h') // List Hash
            {
                test.hashList(); // Calls display function in HashTable
            }
            else if (key == 'b') // List BST Key
            {
                test.bstKey(); // Calls displayKey from DataRecord
			}
		}
        
        else if (key == 'p') // Print Indented Tree
        {
			test.printTree(); // Calls printTree function from DataRecord (prints only name of restaurant)
        }
        
        else if (key=='h') // Use HashTable to search
        {
            test.hashStats(); // Calls displayStats function in HashTable
        }

        else if (key=='b') // Backup
        {
			backup = true;
            test.backUp();
        }
		///////////////////////////-----------------------------

        else if (backup && key == 'u') // Use backup
        {
			backup = false;
            test.useBackup();
        }
        else if (key == 'c') // Compare
        {
			test.compare();
        }

        else if (key == 'm')
        {
			int num = 0;
			string input;
			bool validInput;

			do
			{
				validInput = true;
			    cout << "Most searched restaurant: "<< endl;
				cout << "How many restaurants do you want to display (max is 10): ";
				cin >> input;
				cin.ignore (100, '\n');
				if (input.size() >= 100)
				{
					validInput = false;
				}
				else
				{
					for (int i = 0; i < input.size() && validInput; i++)
					{
						if (isalpha(input[i]))
						{
							validInput = false;
						}
					}
				}
				if (!validInput)
				{
					cout << "Invalid input. Input is only number from 1 to 10.\n";
				}
			} while (!validInput);

			istringstream convert (input);
			if (!(convert >> num))
				num = 10;

			if (num > 10)
				num = 10;
			test.mostSearched(num);
        }


        else if (key == 's')
        {
			save = test.save();
        }
        
        else if (key != 'q')
            cout << "Not a valid menu choice."<< endl;
        
        else if (key == 'q' && save == false) // Appears only if no save was completed
        {
			do
			{
				cout << "\t y. Quit without saving data" << endl
					 << "\t n. Do Not Quit & Save Data" << endl;
				cout << "Choice: ";
				cin >> key;
				key = tolower(key);

				cin.ignore (100, '\n');

			} while (key != 'n' && key != 'y');

            if (key=='n')
            {
                save = test.save();
				return 0;
            }
			else
				return 0;
        }
    }
	
}
