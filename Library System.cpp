#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

//Book has id, title, and author.

//Prototypes
void run();
void welcome();
void mainMenu();
void addBook(string title, string author);
int searchBook(int id);
void removeBook(int id);
void updateBook(int id);
void borrowBook(int id);
void returnBook(int id);
void displayBook();
pair<bool, int> isAvailable(int id);

//Valuables Vars.
const int bookCapacity = 100;
int availableBooksNo = 0;
int autoID = 1;

//Arrays
int bookID[bookCapacity];
string bookTitle[bookCapacity];
string bookAuthor[bookCapacity];
bool bookAvailability[bookCapacity];

int main()
{
	run();
}

void run()
{
	int choice, id;
	string title, author;

	system("color B0");
	welcome();
	Sleep(2000);
	system("cls");

	while (true)
	{
		system("cls");

		mainMenu();

		cout << "Pick a number: ";
		cin >> choice;


		switch (choice)
		{
		case 1:
			system("cls");
			displayBook();
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "Enter a book ID to update: ";
			cin >> id;
			updateBook(id);
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "Enter the tile of the book: ";
			cin.ignore();
			getline(cin, title);

			cout << "Enter the author of the book: ";
			getline(cin, author);

			addBook(title, author);

			system("pause");
			break;
		case 4:
			system("cls");
			cout << "Enter the id of the book you want to remove: ";
			cin >> id;
			removeBook(id);
			system("pause");
			break;
		case 5:
			system("cls");
			cout << "enter the book id you want to borrow: ";
			cin >> id;
			borrowBook(id);
			system("pause");
			break;
		case 6:
			system("cls");
			cout << "Enter the book id you want to return: ";
			cin >> id;
			returnBook(id);
			system("pause");
			break;
		case 7:
			system("cls");
			cout << "Thank you for using Alex Library :)\n";
			Sleep(2000);
			return;
		default: cout << "You should pick a number between 1 - 7";
			break;
		}
	}
}

void welcome()
{
	// Print "ALEX LIBRARY" using ##
	cout << endl << endl << endl;

	cout << "\t\t\t\t\t\t  ######    ##          ########    ##     ##  \n";
	cout << "\t\t\t\t\t\t ##    ##   ##          ##           ##   ##   \n";
	cout << "\t\t\t\t\t\t ##    ##   ##          ##            ####    \n";
	cout << "\t\t\t\t\t\t ########   ##          ######        ####    \n";
	cout << "\t\t\t\t\t\t ##    ##   ##          ##           ##  ##   \n";
	cout << "\t\t\t\t\t\t ##    ##   ##          ##          ##    ##  \n";
	cout << "\t\t\t\t\t\t ##    ##   ########     ########  ##      ##  \n";

	cout << endl << endl << endl;

	cout << "\t\t\t\t    ##        ########  ########   ########   ########  ########  ##     ##  \n";
	cout << "\t\t\t\t    ##          ##      ##    ##   ##    ##   ##    ##  ##    ##  ##   ##   \n";
	cout << "\t\t\t\t    ##          ##      ########   ########   ##    ##  ########   ## ##    \n";
	cout << "\t\t\t\t    ##          ##      ##    ##   ##  ##     ########  ##  ##       ##     \n";
	cout << "\t\t\t\t    ##          ##      ##    ##   ##   ##    ##    ##  ##   ##      ##     \n";
	cout << "\t\t\t\t    ##          ##      ##    ##   ##    ##   ##    ##  ##    ##     ##     \n";
	cout << "\t\t\t\t    ########  ########  ########   ##    ##   ##    ##  ##    ##     ##     \n";
}

void mainMenu()
{
	cout << "What do you need: \n\n";

	cout << "1- List all books.\n" << endl
		<< "2- Update an existing book.\n" << endl
		<< "3- Add a new book.\n" << endl
		<< "4- Remove a book.\n" << endl
		<< "5- Borrow a book.\n" << endl
		<< "6- Return a book.\n" << endl
		<< "7- Exit.\n" << endl;
}

void addBook(string title, string author)
{
	bookID[availableBooksNo] = autoID;
	bookTitle[availableBooksNo] = title;
	bookAuthor[availableBooksNo] = author;
	bookAvailability[availableBooksNo] = true;

	cout << title + " book is added successfully.\n";

	availableBooksNo++;
	autoID++;
}

int searchBook(int id)
{
	for (int i = 0; i < availableBooksNo; i++)
	{
		if (bookID[i] == id) {
			return i;
		}
	}

	return -1;
}

void removeBook(int id)
{
	int position = isAvailable(id).second;

	if (position == -1)
	{
		cout << "There is no book by this ID.\n";
		return;
	}

	//if exists

	//Shifitng -> deleting
	for (int i = position; i < availableBooksNo; i++)
	{
		bookID[i] = bookID[i + 1];
		bookTitle[i] = bookTitle[i + 1];
		bookAuthor[i] = bookAuthor[i + 1];
		bookAvailability[i] = bookAvailability[i + 1];
	}

	//Updating the No. of existing books.
	availableBooksNo--;
	cout << "The book has been deleted successfully.\n";
}

void updateBook(int id)
{
	int position = isAvailable(id).second;
	bool found = isAvailable(id).first;

	if (found)
	{
		string title, author;

		cout << "Type the book title: ";
		cin.ignore();
		getline(cin, title);


		cout << "Type the book author: ";
		cin.ignore();
		getline(cin, author);

		bookTitle[position] = title;
		bookAuthor[position] = author;
	}
	else
	{
		cout << "There is no book with this ID.\n";
	}


}

void borrowBook(int id)
{
	bool found = isAvailable(id).first;
	int position = isAvailable(id).second;

	if (found)
	{
		if (bookAvailability[position])
		{
			bookAvailability[position] = false;
			cout << "The book is borrowed successfully.\n";
		}
		else
		{
			cout << "Sorry, this book is already borrowed. :(\n";
		}
	}
	else
	{
		cout << "There is no book by this ID.\n";
	}
}

void returnBook(int id)
{
	bool found = isAvailable(id).first;
	int position = isAvailable(id).second;

	if (found)
	{
		if (bookAvailability[position])
		{
			cout << "The book already exists.\n";
		}
		else
		{
			bookAvailability[position] = true;
			cout << "The book is returned successfully. :)\n";
		}
	}
	else
	{
		cout << "There is no book by this ID.\n";
	}
}

void displayBook()
{
	for (int i = 0; i < availableBooksNo; i++)
	{
		cout << "ID: " << bookID[i] << endl
			<< "Book title: " << bookTitle[i] << endl
			<< "Book Author: " << bookAuthor[i] << endl
			<< "Status: " << (bookAvailability[i] ? "Available\n" : "Not available\n")
			<< " ======================================\n\n";
	}
}

pair<bool, int> isAvailable(int id)
{
	int position = searchBook(id);

	if (position == -1)
	{
		return { false, position };
	}
	else
	{
		return { true, position };
	}
}