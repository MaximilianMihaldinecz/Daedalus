#include "LevelSelectionMenu.h"
#include<ostream>
#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>

using namespace std;


LevelSelectionMenu::LevelSelectionMenu()
{
}

//Draws the list of levels.
void LevelSelectionMenu::DrawLevelSelectionScreen()
{
	string options[] = { "Very easy (10 rooms)", "Easy (20 rooms)", "Moderate (30 rooms)", "Hard (40 rooms)","Extreme (1000 rooms)","Back to main menu" };
	
	ClearScreen();
	DrawHeader();
	MoveCursor(15, 2);
	DrawOptionsListDesription("Select the difficulty level (enter a number):");
	DrawOptionsList(options, NULL, 6, true);
	MoveCursor(16, 2);
	cout << "Select: ";
}

//Displays the level selection screen and gets the user input.
int LevelSelectionMenu::Draw()
{
	int selection = 0;
	while (selection < 1 || selection > 6)
	{
		DrawLevelSelectionScreen();
		selection = GetSelection();
	}

	if (selection == 6)
	{
		selection = 0;
	}

	return selection;
}

LevelSelectionMenu::~LevelSelectionMenu()
{
}
