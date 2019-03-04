#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;

//Global Variables
const int NUMBER_OF_RECORDS = 1000;
const int NAME_LENGTH = 35;
const char FILENAME[] = "PhoneBook.txt";

//Function prototype
void DisplayMenu(int& menuSelection);

void ProcessMenu(int& menuSelection, bool & valid, char recordOfNames[][NAME_LENGTH],
	double recordOfPhoneNumbers[], int recordOfBirthDates[], int & numberOfRecords);

int GetDataBase(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords);

void PostDataBase(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[], 
	int recordOfBirthDates[], int & numberOfRecords);

void BubbleSort(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords);

int Search(char recordOfNames[][NAME_LENGTH], int & numberOfRecords);

int BinarySearch(char recordOfNames[][NAME_LENGTH], char target[], int & numberOfRecords);

void AddRecord(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[], 
	int recordOfBirthDates[], int & numberOfRecords);

void EditRecord(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numOfRecords);

void DisplayDB(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[], 
	int recordOfBirthDates[], int & numberOfRecords);

void DisplayDB(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords, int index);

//Functions
int main()
{
	int menuSelection = 0; //Holds selction from the menu
	bool valid = true; //Keeps program running
	int PassFailToken = 1; // if >0 success or <0 fail or =0 unkown fatel error
	int numberOfRecords = 0; // Holds the number of records pulled from DB at time of Load

	//Will contain all the records from the database when loaded
	char recordOfNames[NUMBER_OF_RECORDS][NAME_LENGTH];
	double recordOfPhoneNumbers[NUMBER_OF_RECORDS];
	int recordOfBirthDates[NUMBER_OF_RECORDS];

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
		cin.clear();
		cin.ignore();

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
	double recordOfPhoneNumbers[], int recordOfBirthDates[], int & numberOfRecords)
{
	int index = 0;

	switch (menuSelection)
	{
	case 1:
		index = Search(recordOfNames, numberOfRecords);
		DisplayDB(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords, index);
		system("pause");
		break;
	case 2:
		AddRecord(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);
		break;
	case 3:
		EditRecord(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);
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

int GetDataBase(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords)
{
	bool valid = false;
	ifstream ReadDB;
	ReadDB.open(FILENAME);

	if (ReadDB.is_open())
	{
		valid = true;

		ReadDB.getline(recordOfNames[numberOfRecords], NAME_LENGTH, ',');
			ReadDB >> recordOfPhoneNumbers[numberOfRecords]
			>> recordOfBirthDates[numberOfRecords];

		while (!ReadDB.eof())
		{
			numberOfRecords++;
			ReadDB.getline(recordOfNames[numberOfRecords], NAME_LENGTH, ',');
			ReadDB >> recordOfPhoneNumbers[numberOfRecords]
				>> recordOfBirthDates[numberOfRecords];
		}
		ReadDB.close();
	}
	else if (ReadDB.fail())
	{
		valid = false;
	}

	BubbleSort(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);

	return valid;
}

void PostDataBase(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords)
{
	char newline = '\n';
	char temp[NAME_LENGTH] = {"\n"};

	for (int ii = 0; ii < numberOfRecords; ii++)
	{
		if (recordOfNames[0][0] == newline)
		{
			for(int jj = 0; jj < NAME_LENGTH; jj++)
			{
				recordOfNames[0][jj] = recordOfNames[0][jj + 1];
			}
		}
		else if (recordOfNames[ii][0] != newline && ii != 0)
		{
			strcat(temp, recordOfNames[ii]);
			strcpy(recordOfNames[ii], temp);
		}
	}
	ofstream WriteDB(FILENAME);

	if (WriteDB.is_open())
	{
		for (int ii = 0; ii < numberOfRecords; ii++)
		{
			WriteDB << recordOfNames[ii] << ", "
				<< fixed << setprecision(0) << recordOfPhoneNumbers[ii] << " "
				<< recordOfBirthDates[ii];
		}
		WriteDB << endl;

		WriteDB.close();
	}
	else if (WriteDB.fail())
	{
		cout << "\t\nFATEL ERROR\n DataBase failed to load.";
	}
}

void BubbleSort(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords)
{
	bool sorted = false;
	char * lname1;
	char * lname2;
	char tempstring[NAME_LENGTH]; 
	int tempint;
	double tempdouble;

	for (int ii = 0; ii < numberOfRecords; ii++)
	{
		for (int jj = 0; jj < numberOfRecords - ii - 1; jj++)
		{
			char name1[NAME_LENGTH];
			char name2[NAME_LENGTH];

			strcpy(name1, recordOfNames[jj]);
			strcpy(name2, recordOfNames[jj + 1]);

			lname1 = strtok(name1, "\n "); 
			lname1 = strtok(NULL, " ");
			lname2 = strtok(name2, "\n ");
			lname2 = strtok(NULL, " ");

			if (strcmp(lname1, lname2) > 0)
			{

				strcpy_s(tempstring, recordOfNames[jj]);
				strcpy_s(recordOfNames[jj], recordOfNames[jj + 1]);
				strcpy_s(recordOfNames[jj + 1], tempstring);

				tempdouble = recordOfPhoneNumbers[jj];
				recordOfPhoneNumbers[jj] = recordOfPhoneNumbers[jj + 1];
				recordOfPhoneNumbers[jj + 1] = tempdouble;

				tempint = recordOfBirthDates[jj];
				recordOfBirthDates[jj] = recordOfBirthDates[jj + 1];
				recordOfBirthDates[jj + 1] = tempint;
			}
		}
	}
}

int Search(char recordOfNames[][NAME_LENGTH], int & numberOfRecords)
{
	char searchName[NAME_LENGTH];
	//char temp[] = "\n";

	cout << "Search by LastName.\n";
	cout << "Name: ";
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(searchName, NAME_LENGTH);
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	return BinarySearch(recordOfNames, searchName, numberOfRecords);
}

void AddRecord(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords)
{
	bool valid = true;
	int selection = 0;

	for(int ii = numberOfRecords; valid || ii + numberOfRecords == 1000; ii++)
	{
		char temp[NAME_LENGTH] = "\n";
		numberOfRecords++;
		cout << "\nEnter Name: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(recordOfNames[ii], NAME_LENGTH);
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		strcat_s(temp, recordOfNames[ii]);
		strcpy_s(recordOfNames[ii], temp);
		

		cout << "\nEnter Phone Number: ";
		cin >> recordOfPhoneNumbers[ii];
		//5 416 225 315
		cout << "\nEnter BirthDate: ";
		cin >> recordOfBirthDates[ii];

		cout << "1...............Add Another Record.\n";
		cout << "2.............................Stop.\n";
		cout << "Selection: ";
		cin >> selection;

		if (selection != 1) valid = false;

		BubbleSort(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);
	}
}

void EditRecord(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords)
{
	int selection = 0;
	char temp[NAME_LENGTH] = "\n";

	int index = Search(recordOfNames, numberOfRecords);

	if (index == -1) cout << "Record Not Found";

	else
	{
		DisplayDB(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords, index);

		cout << "\nWhat do you want to change?\n";
		cout << "1.................Name.\n";
		cout << "2.........Phone Number.\n";
		cout << "3...........Birth Date.\n";
		cout << "Selection: ";
		cin >> selection;
		cin.clear();

		switch (selection)
		{
		case 1: 
			cout << "\nEnter  Your New Name: ";
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(recordOfNames[index], NAME_LENGTH);
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());

			strcat_s(temp, recordOfNames[index]);
			strcpy_s(recordOfNames[index], temp);
			break;

		case 2:
			cout << "\nEnter your new phone number: ";
			cin >> recordOfPhoneNumbers[index];
			break;

		case 3:
			cout << "\nEnter your new birthdate: ";
			cin >> recordOfBirthDates[index];
			break;

		default:
			cout << "Invalid entry...";
			system("pause");
			break;
		}

		BubbleSort(recordOfNames, recordOfPhoneNumbers, recordOfBirthDates, numberOfRecords);
	}
}

void DisplayDB(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[], 
	int recordOfBirthDates[], int & numberOfRecords)
{
	for (int ii = 0; ii < numberOfRecords; ii++)
	{
		cout << "____________________________________________________________________________\n";
		cout << setw(NAME_LENGTH)<< left << recordOfNames[ii] 
			<< setw(15) << fixed << setprecision(0) << recordOfPhoneNumbers[ii] 
			<< setw(10) << recordOfBirthDates[ii] << '\n';
		cout << "____________________________________________________________________________\n";
	}
}

void DisplayDB(char recordOfNames[][NAME_LENGTH], double recordOfPhoneNumbers[],
	int recordOfBirthDates[], int & numberOfRecords, int index) 
{
	if (index >= 0) 
	{
		cout << "____________________________________________________________________________\n";
		cout << setw(NAME_LENGTH) << left << recordOfNames[index]
			<< setw(15) << fixed << setprecision(0) << recordOfPhoneNumbers[index]
			<< setw(10) << recordOfBirthDates[index] << '\n';
		cout << "____________________________________________________________________________\n";
	}
	else if (index = -1)
	{
		cout << "\nUnkown error\n";
	}
}

int BinarySearch(char recordOfNames[][NAME_LENGTH], char target[], int & numberOfRecords)
{
	char name1[NAME_LENGTH];
	char * lname;
	bool found = false;
	int start = 0;
	int end = numberOfRecords;
	int middle = 0;
	int index = -1;

	while (start <= end && found != true)
	{
		middle = (start + end) / 2;
		strcpy(name1, recordOfNames[middle]);
		lname = strtok(name1, " ");
		lname = strtok(NULL, " ");

		if (strcmp(target, lname) == 0)
		{
			found = true;
		}
		else if (strcmp(target, lname) > 0)
		{
			start = middle + 1;
		}
		else
			end = middle - 1;
	}

	if (found) index = middle;

	return index;
}