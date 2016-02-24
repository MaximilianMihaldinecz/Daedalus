#pragma once
#include<string>
#include "Labyrinth.h"
#include "InGame.h"

class Player
{
protected:
	int _Health;
	Labyrinth *_Labyrinth;
	InGame *_InGameScreen;

	virtual int DisplayingCurrent() = 0;
	void DisplayIntro();
	void DisplayLost();
	void DisplayWin();
	std::string EndGameStats();

	std::string SpecialMessageForRoomType(short roomType);
	void Move(short response);

public:
	Player();
	virtual int StartGame() =0;
	short GetLabyrinthLength();
	std::string* GetLabyrinthAsString();
	~Player();
};

