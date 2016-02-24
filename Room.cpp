#pragma once
#include "Room.h"
#include<string>
#include "StringList.h"

#include<iostream>

using namespace std;

Room::Room(unsigned char type, string name)
{
	_Type = type;
	_Name = name;
	_Links = NULL;
	_Visited = false;
}

Room::Room()
{
	_Type = 0;
	_Name = "";
	_Links = NULL;
	_Visited = false;
}

//Returns true if the room is already visited
bool Room::IsVisited()
{
	return _Visited;
}

//Sets the room's visited status to a given value
void Room::SetVisit(bool value)
{
	_Visited = value;
}

//Sets the neighbours to the provided array of pointers
void Room::AddLinks(short count, Room **neighbours)
{
	if (_Links != NULL)
	{
		delete[] _Links;
	}
	_Links = neighbours;
	_LinkCount = count;
}

//Sets the name of the room
void Room::SetName(string newName)
{
	_Name = newName;
}

//Returns the name of the room
string Room::GetName()
{
	return _Name;
}

//Sets the type of the room
void Room::setType(unsigned char newType)
{
	_Type = newType;
}

//Returns the type of the room
unsigned char Room::GetType()
{
	return _Type;
}

//Returns the number of neighbors
short Room::GetLinksCount()
{
	return _LinkCount;
}

//Returns an array of strings containing the names of the neighbors
string* Room::GetLinks()
{
	string * links = NULL;
	if (_LinkCount > 0)
	{
		links = new string[_LinkCount];
		for (short i = 0; i < _LinkCount; i++)
		{
			links[i] = _Links[i]->GetName();
		}
	}
	return links;
}

//Returns the names of the neighbors
StringList* Room::GetLinksAsList()
{
	StringList *links = NULL;
	if (_LinkCount > 0)
	{
		links = new StringList();
		for (short i = 0; i < _LinkCount; i++)
		{
			links->Add(_Links[i]->GetName());			
		}
	}
	return links;
}

//Returns a pointer to one of neighbor room.
Room* Room::GetNeighbour(short id)
{
	return _Links[id];
}

Room::~Room()
{
	if (_Links != NULL)
	{
		delete[] _Links;
	}
}
