#pragma once
#include "Room.h"


class LinkedList
{
private:
	Room *_Start;
	Room *_End;
	Room *_Current;

public:
	LinkedList();
	void Add(Room &room);
	~LinkedList();
};

