#include "MainMenu.h"
#include<ostream>
#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>

using namespace std;

MainMenu::MainMenu()
{
}

//Draws the game's short description, displayed under the logo.
void MainMenu::DrawGameInfo()
{
	cout << " Be a sorcerer, a king or a minotaur! Complete all the five difficulty levels!" << endl;
	cout << "       Load your favorite labyrinths from file, or save them to disk!" << endl;
}

//Displays all the elements of the main screen.
void MainMenu::DrawMainScreen(string options[], int length)
{	
	ClearScreen();
	DrawHeader();
	DrawGameInfo();
	MoveCursor(15, 5);
	DrawOptionsListDesription("Select from the menu (enter a number):");	
	DrawOptionsList(options, NULL, length, false);
	MoveCursor(16, 2);
	cout << "Select: ";
}

//Calling the Draw() with the default value (no save option)
int MainMenu::Draw()
{
	return Draw(false);
}

//Displays the main menu with or without the save option.
int MainMenu::Draw(bool hasSave)
{
	int selection = 0;
	short firstElement = 1;
	short lastElement = 3 + hasSave;

	string *options = new string[lastElement];
	if (lastElement == 3)
	{
		options[0] = "Start new game";
		options[1] = "Load labyrinth from file";
		options[2] = "Exit";
	}
	else
	{
		options[0] = "Start new game";
		options[1] = "Load labyrinth from file";
		options[2] = "Save current labyrinth to file";
		options[3] = "Exit";
	}

	while (selection < firstElement || selection > lastElement)
	{
		DrawMainScreen(options, lastElement);
		selection = GetSelection();
	}

	if (selection == lastElement)
	{
		selection = 0;
	}

	delete [] options;
	return selection;
}

MainMenu::~MainMenu()
{
}
