#include "PlayerSelectionMenu.h"
#include<ostream>
#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>

using namespace std;

PlayerSelectionMenu::PlayerSelectionMenu()
{
}

//Draws the list of characters.
void PlayerSelectionMenu::DrawPlayerSelectionScreen()
{
	string options[] = { "Sorcerer", "King", "Minotaur", "Back to main menu" };
	string descriptions[] = {"Ability: Can cast a magical map of the labyrinth.","Ability: Can mark the visited rooms.","Ability: Can run through multiple rooms (berserk).",""};

	ClearScreen();
	DrawHeader();
	MoveCursor(15, 2);
	DrawOptionsListDesription("Select your character (enter a number):");
	DrawOptionsList(options, descriptions,4,true);
	MoveCursor(16, 2);
	cout << "Select: ";
}

//Displays the player selection screen and gets the user input.
int PlayerSelectionMenu::Draw()
{
	int selection = 0;
	while (selection < 1 || selection > 4)
	{
		DrawPlayerSelectionScreen();
		selection = GetSelection();
	}

	if (selection == 4)
	{
		selection = 0;
	}

	return selection;
}

PlayerSelectionMenu::~PlayerSelectionMenu()
{
}
