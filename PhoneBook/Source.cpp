#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;

//Global Variables
const int NUMBER_OF_RECORDS = 1000;
const int NAME_LENGTH = 35;
const char FILENAME[] = "PhoneBook.txt";

//Function prototype
void DisplayMenu(int& menuSelection);

void ProcessMenu(int& menuSelection, bool & valid, char recordOfNames[][NAME_LENGTH],
	int recordOfPhoneNumbers[], int recordOfBirthDates[], int & numberOfRecords);

int GetDataBase(char recordOfNames[][NAME_LENGTH], int recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords);

void PostDataBase(char recordOfNames[][NAME_LENGTH], int recordOfPhoneNumbers[], 
	int recordOfBirthDates[], int & numberOfRecords);

int Search(char recordOfNames[][NAME_LENGTH], int & numberOfRecords);

void AddRecord(char recordOfNames[][NAME_LENGTH], int recordOfPhoneNumbers[], 
	int recordOfBirthDates[], int & numberOfRecords);

void DisplayDB(char recordOfNames[][NAME_LENGTH], int recordOfPhoneNumbers[], 
	int recordOfBirthDates[], int & numberOfRecords);

//Functions
int main()
{
	int menuSelection = 0; //Holds selction from the menu
	bool valid = true; //Keeps program running
	int PassFailToken = 1; // if >0 success or <0 fail or =0 unkown fatel error
	int numberOfRecords = 0; // Holds the number of records pulled from DB at time of Load

	//Will contain all the records from the database when loaded
	char recordOfNames[NUMBER_OF_RECORDS][NAME_LENGTH];
	int recordOfPhoneNumbers[NUMBER_OF_RECORDS] = { 0 };
	int recordOfBirthDates[NUMBER_OF_RECORDS] = { 0 };

	//Opens DB and scrapes all data
	valid = GetDataBase(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);

	while(valid)
	{
		DisplayMenu(menuSelection);
		ProcessMenu(menuSelection, valid, recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);
	}

	//Opens Db and rewrites all the data
	PostDataBase(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);

	return 0;
}

void DisplayMenu(int& menuSelection)
{
	bool valid = false;
	do
	{
		system("cls");
		cout << "\t Please enter the number for the menu item you would like to select.";
		cout << "\n1......................................................Find Record.\n";
		cout << "2.......................................................Add Record.\n";
		cout << "3......................................................Edit Record.\n";
		cout << "4............................................Display Entire Record.\n";
		cout << "5..................................................Exit Phone Book.\n";
		cout << "\nPlease enter your selection: ";
		cin >> menuSelection;

		if (menuSelection > 5 || menuSelection < 1)
		{
			cout << "\n" << menuSelection << " is an invalid option.\n";
			valid = true;
			system("pause");
		}
		else valid = false;

	} while (valid);
}

void ProcessMenu(int& menuSelection, bool & valid, char recordOfNames[][NAME_LENGTH],
	int recordOfPhoneNumbers[], int recordOfBirthDates[], int & numberOfRecords)
{
	int index = 0;

	switch (menuSelection)
	{
	case 1:
		index = Search(recordOfNames, numberOfRecords);
		system("pause");
		break;
	case 2:
		AddRecord(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);
		break;
	case 3:
		break;
	case 4:
		DisplayDB(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);
		system("pause");
		break;
	case 5:
		valid = false;
		break;
	default:
		cout << "\nUnkown Error has occured.\n";
		system("pause");
		break;
	}
}

int GetDataBase(char recordOfNames[][NAME_LENGTH], int recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords)
{
	bool valid = false;
	ifstream ReadDB;
	ReadDB.open(FILENAME);

	if (ReadDB.is_open())
	{
		valid = true;

		ReadDB >> recordOfNames[numberOfRecords]
			>> recordOfPhoneNumbers[numberOfRecords]
			>> recordOfBirthDates[numberOfRecords];

		while (!ReadDB.eof())
		{
			ReadDB >> recordOfNames[numberOfRecords]
				>> recordOfPhoneNumbers[numberOfRecords]
				>> recordOfBirthDates[numberOfRecords];

			numberOfRecords++;
		}
		ReadDB.close();
	}
	else if (ReadDB.fail())
	{
		valid = false;
	}

	return valid;
}

void PostDataBase(char recordOfNames[][NAME_LENGTH], int recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords)
{
	ofstream WriteDB(FILENAME);

	if (WriteDB.is_open())
	{
		for (int ii = 0; ii < numberOfRecords; ii++)
		{
			if (ii != numberOfRecords - 1) 
			{
				WriteDB << recordOfNames[ii] << " "
					<< recordOfPhoneNumbers[ii] << " "
					<< recordOfBirthDates[ii] << endl;
			}
			else
			{
				WriteDB << recordOfNames[ii] << " "
					<< recordOfPhoneNumbers[ii] << " "
					<< recordOfBirthDates[ii];
			}
		}

		WriteDB.close();
	}
	else if (WriteDB.fail())
	{
		cout << "\t\nFATEL ERROR\n DataBase failed to load.";
	}


}

int Search(char recordOfNames[][NAME_LENGTH], int & numberOfRecords)
{
	char searchName[NAME_LENGTH];
	int index = 0;

	cout << "Search by Name.\n";
	cout << "Name: ";
	cin >> searchName;

	for (int ii = 0; ii < numberOfRecords; ii++)
	{
		if (strcmp(searchName, recordOfNames[ii]) == 0)
		{
			index = ii;
		}
	}

	return index;
}

void AddRecord(char recordOfNames[][NAME_LENGTH], int recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords)
{
	bool valid = true;
	int selection = 0;

	for(int ii = numberOfRecords; valid || ii + numberOfRecords == 1000; ii++)
	{

		numberOfRecords++;
		cout << "\nEnter Name: ";
		cin.ignore();
		cin.getline(recordOfNames[ii], NAME_LENGTH);

		cout << "\nEnter Phone Number: ";
		cin >> recordOfPhoneNumbers[ii];

		cout << "\nEnter BirthDate: ";
		cin >> recordOfBirthDates[ii];

		cout << "1...............Add Another Record.\n";
		cout << "2.............................Stop.\n";
		cin >> selection;

		if (selection != 1) valid = false;

	}
}

void DisplayDB(char recordOfNames[][NAME_LENGTH], int recordOfPhoneNumbers[], 
	int recordOfBirthDates[], int & numberOfRecords)
{
	for (int ii = 0; ii < numberOfRecords; ii++)
	{
		cout << recordOfNames[ii] << "         " << recordOfPhoneNumbers[ii] << "                    " << recordOfBirthDates[ii] << '\n';
	}
}