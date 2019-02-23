#include <iostream>
#include <fstream>
#include <string>

using std::getline;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::ios;

const int NUMBER_OF_RECORDS = 1000;
const int BUFFER_SIZE = 15;
const int NAME_LENGTH = 35;

void DisplayMenu(int& menuSelection);
void ProcessMenu(int& menuSelection, bool& valid);
void GetData(char aName[][NAME_LENGTH], int& bufferIndex);
void GetData(char aName[][NAME_LENGTH],
			int aPhoneNumber[],
			int aBirthDate[], int& bufferIndex);

int LoadDataBase(char recordOfName[][NAME_LENGTH],
			int recordOfPhoneNumbers[], int recordOfBirthDates[],
			int& numberOfRecords);

bool Tests(int & PassFailToken);



int main()
{
	int menuSelection = 0; //Holds selction from the menu

	bool valid = true; //Keeps program running

	int PassFailToken = 1; // if >0 success or <0 fail or =0 unkown fatel error

	int numberOfRecords = 0; // Holds the number of records pulled from DB at time of Load

	int bufferIndex = 0; //Holds the number of records stored in the buffer

	//Will contain all the records from the database when loaded
	char recordOfName[NUMBER_OF_RECORDS][NAME_LENGTH];
	int recordOfPhoneNumbers[NUMBER_OF_RECORDS];
	int recordOfBirthDates[NUMBER_OF_RECORDS];
	
	//buffer of records
	char aName[BUFFER_SIZE][NAME_LENGTH];
	int aPhoneNumber[BUFFER_SIZE];
	int aBirthDate[BUFFER_SIZE];

	//Opens DB and scrapes all data
	PassFailToken = LoadDataBase( recordOfName, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);
	valid = Tests(PassFailToken);

	while(valid)
	{
		DisplayMenu(menuSelection);
		ProcessMenu(menuSelection, valid);
	}


	return 0;
}

void DisplayMenu(int& menuSelection)
{
	bool valid = false;
	do
	{
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

	} while (valid);
}

void ProcessMenu(int& menuSelection, bool& valid)
{
	/*      Zombie code
	//Will contain all the records from the database when loaded
	char recordOfName[NUMBER_OF_RECORDS][NAME_LENGTH];
	int recordOfPhoneNumbers[NUMBER_OF_RECORDS];
	int recordOfBirthDates[NUMBER_OF_RECORDS];
	int numberOfRecords = 0;
	//buffer of records
	char aName[BUFFER_SIZE][NAME_LENGTH];
	int aPhoneNumber[BUFFER_SIZE];
	int aBirthDate[BUFFER_SIZE];
	int bufferIndex = 0;*/


	switch (menuSelection)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		valid = false;
		break;
	default:
		cout << "\nUnkown Error has occured.\n";
		system("pause");
		break;
	}
}

void GetData(char aName[][NAME_LENGTH], int& bufferIndex)
{
	cout << "\nEnter your full name: ";
	cin.getline(aName[bufferIndex], NAME_LENGTH);
	bufferIndex++;
}

void GetData(char aName[][NAME_LENGTH],
	int aPhoneNumber[], int aBirthDate[], int& bufferIndex)
{
	cout << "\nEnter your full name: ";
	cin.getline(aName[bufferIndex], NAME_LENGTH);

	cout << "\nEnter your phone number with only numbers: ";
	cin >> aPhoneNumber[bufferIndex];

	cout << "\nEnter your birth date with only numbers: ";
	cin >> aBirthDate[bufferIndex];

	bufferIndex++;
}

int LoadDataBase(char recordOfName[][NAME_LENGTH],
	int recordOfPhoneNumbers[],
	int recordOfBirthDates[], int& numberOfRecords)
{
	int PassFailToken = 0;
	ifstream readPhoneBook("PhoneBook.txt", ios::app);

	if (readPhoneBook.is_open())
	{
		PassFailToken = 1;

		readPhoneBook >> recordOfName[numberOfRecords]
		 >> recordOfPhoneNumbers[numberOfRecords]
		 >> recordOfBirthDates[numberOfRecords];

		while (!readPhoneBook.eof())
		{
			readPhoneBook >> recordOfName[numberOfRecords]
				>> recordOfPhoneNumbers[numberOfRecords]
				>> recordOfBirthDates[numberOfRecords];
		}
		readPhoneBook.close();
	}
	else if (readPhoneBook.fail())
	{
		PassFailToken = -1;
	}

	return PassFailToken;
}


bool Tests(int & PassFailToken)
{
	bool valid = true;
	if (PassFailToken > 0)
	{
		valid = true;
	}
	else if (PassFailToken < 0)
	{
		cout << "Failed";
		valid = false;
	}
	else if (PassFailToken == 0)
	{
		cout << "An unkown fatel error hased occured...";
		valid = false;
	}
	return valid;
}