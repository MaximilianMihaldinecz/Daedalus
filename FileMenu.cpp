#include "FileMenu.h"
#include<ostream>
#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>

using namespace std;

FileMenu::FileMenu()
{
}

//Not applicable, the return value must be string.
int FileMenu::Draw()
{
	return 0;
}

//Draws the load or save screen without warning message
string FileMenu::Draw(bool isLoad)
{
	return Draw(isLoad, false);
}

//Draws the load or save screen with or without warning message
string FileMenu::Draw(bool isLoad, bool errorMsg)
{
	string header;
	string message;
	string example = "Example: C:/folder/file.txt";
	string error;

	if (isLoad == true)
	{
		header = "___Load an existing labyrinth from file___";
		message = "Type in the full path of the file to load and press Enter.\n(Or type  0 to return to the main menu)";
		error = "Could not load the file.";
	}
	else
	{
		header = "___Save the current labyrinth to a file___";
		message = "Type in the full path of the file to save and press Enter.\n(Or type  0 to return to the main menu)";
		error = "Could not save the file";
	}


	ClearScreen();
	MoveCursor(20, 0);
	cout << header << endl;	
	AddEmptyLines(2);
	cout << message;
	AddEmptyLines(3);
	cout << example;
	AddEmptyLines(2);
	if (errorMsg == true)
	{
		cout << error;
		AddEmptyLines(2);
	}

	string response;
	cin >> response;

	return response;
}

//Displays a confirmation message (when the file saving was successful
void FileMenu::ConfirmSave()
{	
	AddEmptyLines(2);
	cout << "Saving was successful! \nType in 0 and press Enter to return to the main menu\n";
	GetSelection();
}

FileMenu::~FileMenu()
{
}
