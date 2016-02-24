#include "Sorcerer.h"
#include<iostream>
#include "Labyrinth.h"
#include "StringList.h"
#include "InGame.h"

using namespace std;

Sorcerer::Sorcerer(Labyrinth *labyrinth)
{
	_Labyrinth = labyrinth;
	//Same amount of health for the sorcerer as the room count
	_Health = _Labyrinth->GetRoomCount();
	_InGameScreen = new InGame();
}

//Manages getting the data about the current room and pass it
//to the InGame object to display.
int Sorcerer::DisplayingCurrent()
{

	short health = _Health;
	string currentName = _Labyrinth->GetCurrentName(true);
	string specialMsg = SpecialMessageForRoomType(_Labyrinth->GetCurrentType());
	StringList *options = _Labyrinth->GetCurrentNeighbours();
	string specialSkill = _InGameScreen->TextCharacterSkillSorcerer;

	int result = _InGameScreen->Draw(_Health, currentName, specialMsg, options, specialSkill, "");

	delete options;
	return result;
}

//The flow of the whole game with the Sorcerer character
int Sorcerer::StartGame()
{
	DisplayIntro();
	int response = -1;
	bool alive = _Health > 0;
	bool isEnd = _Labyrinth->IsCurrentTheEndNode();

	while (alive == true && isEnd == false && response != 0)
	{
		response = DisplayingCurrent();
		switch (response)
		{
		case 0:
			//Leave the game
			isEnd = true;
			break;
		case 1:
			//Call the special skill
			MagicMap();
			break;
		default:
			//Moving to different room
			Move(response - 2);
			break;
		}

		//Loosing
		if (_Health == 0)
		{
			alive = false;
			DisplayLost();
		}

		//Winning
		if (_Labyrinth->IsCurrentTheEndNode() == true && _Health>0)
		{
			isEnd = true;
			DisplayWin();
		}
	}

	return 0;
}

//Special ability of the Sorcerer, displays all the rooms in the labyrinth.
void Sorcerer::MagicMap()
{
	StringList *allRoomNames = _Labyrinth->GetAllRoomNames();
	_InGameScreen->Draw(allRoomNames,_InGameScreen->TextMagicMapTitle);
	delete allRoomNames;
}


Sorcerer::~Sorcerer()
{
	delete _InGameScreen;
	delete _Labyrinth;
}
