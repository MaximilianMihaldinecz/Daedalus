#pragma once
#include<string>
#include "Room.h"
#include "StringList.h"

class Labyrinth
{
private:
	Room* _Rooms;
	short _RoomCount;
	Room* _CurrentRoom;
	std::string* _StrLabyrinth;

	//statistical data
	//Stores the number of steps the user while walking in the labyrinth
	int _NumberOfSteps;
	

public:
	Labyrinth(std::string* strLabyrinth, short nodes);
	std::string* ToString();
	short GetRoomCount();
	std::string GetCurrentName(bool markAsVisited);
	short GetCurrentType();
	StringList* GetCurrentNeighbours();
	bool IsCurrentTheEndNode();
	bool IsCurrentHealthUpNode();
	bool IsCurrentHealthDownNode();
	void MoveTo(short id);
	void MoveToRandom();
	StringList* GetAllRoomNames();
	StringList* GetAllUnvisitedRoomNames();

	int GetStatNumberOfSteps();
	int GetStatNumberOfVisitedRooms();
	int GetStatPercentageExplored();

	~Labyrinth();
};

