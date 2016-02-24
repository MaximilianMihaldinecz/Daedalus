#include "King.h"
#include "Labyrinth.h"
#include "StringList.h"
#include "InGame.h"

using namespace std;

King::King(Labyrinth *labyrinth)
{
	_Labyrinth = labyrinth;
	//Double health for the king
	_Health = _Labyrinth->GetRoomCount()*2;
	_InGameScreen = new InGame();
}

//Manages getting the data about the current room and pass it
//to the InGame object to display.
int King::DisplayingCurrent()
{
	short health = _Health;
	string currentName = _Labyrinth->GetCurrentName(true);
	string specialMsg = SpecialMessageForRoomType(_Labyrinth->GetCurrentType());
	StringList *options = _Labyrinth->GetCurrentNeighbours();
	string specialSkill = _InGameScreen->TextCharacterSkillKing;

	int result = _InGameScreen->Draw(_Health, currentName, specialMsg, options, specialSkill, "");

	delete options;
	return result;
}

//The flow of the whole game with the King character
int King::StartGame()
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
			Wisdom();
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

//Special ability of the king, display the list of unvisited rooms.
void King::Wisdom()
{
	StringList *unVistiedRoomNames = _Labyrinth->GetAllUnvisitedRoomNames();
	_InGameScreen->Draw( unVistiedRoomNames, _InGameScreen->TextWisdomTitle);
	delete unVistiedRoomNames;
}

King::~King()
{
	delete _InGameScreen;
	delete _Labyrinth;

}
