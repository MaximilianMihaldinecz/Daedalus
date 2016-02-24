#include "ConsoleForm.h"
#include<ostream>
#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>

using namespace std;

ConsoleForm::ConsoleForm()
{
}

//Clears the screen.
//On windows systems, it uses built in cls command.
//On any other systems (assuming Unix), it uses the clear command
void ConsoleForm::ClearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif	
}

//Draws the logo of the program
void ConsoleForm::DrawHeader()
{

	cout << "           ________                    .___      .__                " << endl;
	cout << "           \\______ \\ _____    ____   __| _/____  |  |  __ __  ______" << endl;
	cout << "            |    |  \\\\__  \\ _/ __ \\ / __ |\\__  \\ |  | |  |  \\/  ___/" << endl;
	cout << "            |    `   \\/ __ \\\\  ___// /_/ | / __ \\|  |_|  |  /\\___ \\ " << endl;
	cout << "           /_______  (____  /\\___  >____ |(____  /____/____//____  >" << endl;
	cout << "                   \\/     \\/     \\/     \\/     \\/                \\/ " << endl;
	cout << "                       Daedalus - Escape from the labyrinth         " << endl;
	cout << endl;
}

//Draws a specific number of empty lines
void ConsoleForm::AddEmptyLines(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		cout << endl;
	}
}

//Draws a specific number of space characters
void ConsoleForm::AddSpaceCharacters(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		cout << ' ';
	}
}

//Moves the cursor to a specific location.
//Relative from the current location.
void ConsoleForm::MoveCursor(int x, int y)
{
	AddEmptyLines(y);
	AddSpaceCharacters(x);
}

//Prints out the description for an option list box
void ConsoleForm::DrawOptionsListDesription(string description)
{
	cout << description << endl;
}

//Prints out the list of options (menu) the user can choose from.
void ConsoleForm::DrawOptionsList(const string options[], const string description[],int length, bool spaceLast)
{
	for (int i = 0; i < length; i++)
	{		
		
		if (spaceLast && i == length - 1)
		{
			MoveCursor(16, 2);
		}
		else
		{
			MoveCursor(16, 1);
		}

		cout << i + 1 << ".     " << options[i];
		if (description != NULL)
		{
			MoveCursor(16, 1);
			cout << "          " << description[i];
		}
	}
}

//Returns a numeric user input.
//Returns -100 if invalid value provided.
int ConsoleForm::GetSelection()
{
	int response = 0;
	cin >> response;
	if (cin.fail())
	{
		response = -100;
	}
	cin.clear();
	cin.ignore(1000, '\n');
	return response;
}

ConsoleForm::~ConsoleForm()
{
}
