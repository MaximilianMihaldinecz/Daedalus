#pragma once
#include "Player.h"
#include<string>
#include "Labyrinth.h"
#include "StringList.h"


class Minotaur :
	public Player
{
private:
	virtual int DisplayingCurrent();
	void Berserk();

public:
	Minotaur(Labyrinth *labyrinth);
	int StartGame();
	~Minotaur();
};

