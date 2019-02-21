#include <iostream>
#include <fstream>
#include <string>

using std::getline;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::ios;

void DisplayMenu(int& menuSelection);
void ProcessMenu(int& menuSelection, bool& valid);
void GetData(char aName[][NAME_LENGTH], int& bufferIndex);
void GetData(char aName[][NAME_LENGTH],
			int aPhoneNumber[],
			int aBirthDate[], int& bufferIndex);

int LoadDataBase(char recordOfName[][NAME_LENGTH], int recordOfPhoneNumbers[], int recordOfBirthDates[], int& numberOfRecords);

const int NUMBER_OF_RECORDS = 1000;
const int BUFFER_SIZE = 15;
const int NAME_LENGTH = 35;


int main()
{
	int menuSelection = 0;
	bool valid = true;

	do
	{
		DisplayMenu(menuSelection);
		ProcessMenu(menuSelection, valid);
	} while (valid);


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
	//Will contain all the records from the database when loaded
	char recordOfName[NUMBER_OF_RECORDS][NAME_LENGTH];
	int recordOfPhoneNumbers[NUMBER_OF_RECORDS];
	int recordOfBirthDates[NUMBER_OF_RECORDS];
	int numberOfRecords = 0;
	//buffer of records
	char aName[BUFFER_SIZE][NAME_LENGTH];
	int aPhoneNumber[BUFFER_SIZE];
	int aBirthDate[BUFFER_SIZE];
	int bufferIndex = 0;


	switch (menuSelection)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		valid = false;
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
	int records = 0;
	ifstream readPhoneBook("PhoneBook.txt", ios::app);

	if (readPhoneBook.is_open())
	{
		readPhoneBook >> recordOfName[records]
		 >> recordOfPhoneNumbers[records]
		 >> recordOfBirthDates[records];

		while (!readPhoneBook.eof())
		{
		}

		readPhoneBook.close();
	}
}