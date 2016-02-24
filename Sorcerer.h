#pragma once
#include "Player.h"
#include<string>
#include "Labyrinth.h"
#include "StringList.h"


class Sorcerer :
	public Player
{
private:
	virtual int DisplayingCurrent();
	void MagicMap();

public:
	Sorcerer(Labyrinth *labyrinth);
	int StartGame();
	~Sorcerer();
};

