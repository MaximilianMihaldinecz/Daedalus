#pragma once
#include "Player.h"
#include<string>
#include "Labyrinth.h"
#include "StringList.h"


class King :
	public Player
{
private:
	virtual int DisplayingCurrent();
	void Wisdom();

public:
	King(Labyrinth *labyrinth);
	int StartGame();
	~King();
};

