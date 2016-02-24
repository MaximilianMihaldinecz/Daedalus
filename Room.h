#pragma once
#include<string>
#include "StringList.h"

class Room
{
private:
	std::string _Name;
	unsigned char _Type;
	Room **_Links;
	short _LinkCount;
	bool _Visited;

public:
	Room(unsigned char type, std::string name);
	std::string GetName();
	unsigned char GetType();
	short GetLinksCount();
	void SetName(std::string newName);
	void setType(unsigned char newType);
	void AddLinks(short count, Room **neighbours);
	std::string* GetLinks();
	StringList* GetLinksAsList();
	Room* GetNeighbour(short id);
	bool IsVisited();
	void SetVisit(bool value);
	Room();
	~Room();
};

