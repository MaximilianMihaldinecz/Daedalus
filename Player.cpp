#include "Player.h"
#include<iostream>
#include "Labyrinth.h"

using namespace std;

Player::Player()
{
	_Labyrinth = NULL;
	_Health = 0;
	_InGameScreen = NULL;
}

//Returns a string containing the end game statistics
string Player::EndGameStats()
{
	string result = "End game statistics:\n\n";
	result += "Number of steps: " + std::to_string(_Labyrinth->GetStatNumberOfSteps());
	result += "\n";
	result += "Number of visited rooms: " + std::to_string(_Labyrinth->GetStatNumberOfVisitedRooms());
	result += "\n";
	result += "Percentage of labyrinth explored: " + std::to_string(_Labyrinth->GetStatPercentageExplored());
	result += "\n";
	return result;
}

//Displays the intro screen
void Player::DisplayIntro()
{
	_InGameScreen->Draw(_InGameScreen->TextIntro, _InGameScreen->TextIntroCursor);
}

//Displays the winning screen
void Player::DisplayWin()
{
	_InGameScreen->Draw(_InGameScreen->TextSpecialEndNode + EndGameStats(), _InGameScreen->TextEndCursor);
}

//Displays the loosing screen
void Player::DisplayLost()
{
	_InGameScreen->Draw(_InGameScreen->TextLostGame + EndGameStats(), _InGameScreen->TextLostGameCursor);
}

//Returns a string containing a special message based on the room type
string Player::SpecialMessageForRoomType(short roomType)
{
	string result = "";
	switch (roomType)
	{
	case 1:
		result = _InGameScreen->TextSpecialEndNode;
		break;
	case 3:
		result = _InGameScreen->TextSpecialHealthUpNode;
		break;
	case 4:
		result = _InGameScreen->TextSpecialHealthDownNode;
		break;
	default:
		result = "";
		break;
	}
	return result;
}

//Moves the character to the new room selected by the user.
//If the room is special health up/down adjusts the health
void Player::Move(short response)
{
	//Moving
	_Labyrinth->MoveTo(response);

	//Check for health
	if (_Labyrinth->IsCurrentHealthUpNode())
	{
		//Increasing the health with the amount of the nodes
		_Health += _Labyrinth->GetRoomCount();
	}

	if (_Labyrinth->IsCurrentHealthDownNode())
	{
		//Halving the health
		_Health /= 2;
	}

	//Decrease life with 1 after each move, unless it is the end
	if (_Labyrinth->IsCurrentTheEndNode()==false)
	{
		_Health--;
	}
}

//Gets the number of rooms in the labyrinth
short Player::GetLabyrinthLength()
{
	return _Labyrinth->GetRoomCount();
}

//Gets the whole labyrinth as a string which can be saved
//to the file.
string* Player::GetLabyrinthAsString()
{
	return _Labyrinth->ToString();
}

Player::~Player()
{
	delete _InGameScreen;
	delete _Labyrinth;
}
