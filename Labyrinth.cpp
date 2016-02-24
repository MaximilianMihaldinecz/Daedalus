#include "Labyrinth.h"
#include "Room.h"
#include<string>


using namespace std;

//Generates the labyrinth from the given array of strings
Labyrinth::Labyrinth(string* strLabyrinth, short nodes)
{
	_Rooms = new Room[nodes];
	_RoomCount = nodes;
	_NumberOfSteps = 0;
	_CurrentRoom = &_Rooms[0];
	_StrLabyrinth = strLabyrinth;


	//Going through all the strings and extracting elements
	for (short i = 0; i < _RoomCount; i++)
	{
		string actual = strLabyrinth[i];

		//Counting the number of commas in a string.
		//This tells the size of the array need to be declared to store links
		int commaCount = 0;
		for (int j = 0; j < actual.length(); j++)
		{
			if (actual[j] == ',')
			{
				commaCount++;
			}
		}


		//Actual character/loop counter
		int c = 0;
		//Characters are placed in a temporary buffer
		string buffer = "";
		//The room type found or not
		bool typeFound = false;
		//The room name found or not
		bool nameFound = false;

		//This holds the room type
		unsigned char type = 0;
		//This holds the  room name
		string name = "";
		//Contains the links to the neighboring rooms. An array of pointers. 
		Room **links = new Room*[commaCount - 1];
		//Number of links found
		short linkCounter = 0;

		//Extracting data from a single string
		while (c < actual.length())
		{
			if (actual[c] != ',')
			{
				//If not comma append to the buffer
				buffer += actual[c];
			}
			else
			{
				//This is a comma character

				if (typeFound == false)
				{
					//The type found now
					type = stoi(buffer);
					typeFound = true;
				}
				else if (nameFound == false)
				{
					//The name found now
					name = buffer;
					nameFound = true;
				}
				else
				{
					//This is a link, adding it to the list of links
					short linkTo = stoi(buffer);
					_Rooms[linkTo];
					links[linkCounter] = &(_Rooms[linkTo]);
					linkCounter++;
				}
				//Empty the buffer
				buffer = "";
			}

			//Incrementing the loop counter
			c++;

			//If this was the last character, flush out the buffer as a last link
			if (c == actual.length())
			{
				short linkTo = stoi(buffer);
				links[linkCounter] = &(_Rooms[linkTo]);
				linkCounter++;
			}
		}

		//Updating the room's attributes with the extracted data
		_Rooms[i].setType(type);
		_Rooms[i].SetName(name);
		_Rooms[i].AddLinks(commaCount - 1, links);
	}
}

//Returns the number of rooms in the labyrinth
short Labyrinth::GetRoomCount()
{
	return _RoomCount;
}

//Returns the labyrinth in an array of string format
//which can be used for saving to file.
string* Labyrinth::ToString()
{
	return _StrLabyrinth;
}

//Gets the name of the current room
string Labyrinth::GetCurrentName(bool markAsVisited)
{
	if (markAsVisited == true)
	{
		_CurrentRoom->SetVisit(true);
	}
	return _CurrentRoom->GetName();
}

//Returns the type of the current room
short Labyrinth::GetCurrentType()
{
	return _CurrentRoom->GetType();
}

//Returns the names of the current room's neighbours
StringList* Labyrinth::GetCurrentNeighbours()
{
	return _CurrentRoom->GetLinksAsList();
}

//Returns true of the current room is the exit
bool Labyrinth::IsCurrentTheEndNode()
{
	return _CurrentRoom->GetType() == 1;
}

//Returns true if the current room is Health up room
bool Labyrinth::IsCurrentHealthUpNode()
{
	return _CurrentRoom->GetType() == 3;
}

//Returns true if the current room is Health down room
bool Labyrinth::IsCurrentHealthDownNode()
{
	return _CurrentRoom->GetType() == 4;
}

//Changes the current room to one of its neighbours
//The number of the neighbour provided as the parameter
void Labyrinth::MoveTo(short id)
{
	_CurrentRoom = _CurrentRoom->GetNeighbour(id);
	_NumberOfSteps++;
}

//Returns the names of all the rooms in the labyrinth.
//Used for the sorcerer's special skill.
StringList* Labyrinth::GetAllRoomNames()
{
	StringList* result = new StringList();

	for (int i = 0; i < _RoomCount; i++)
	{
		result->Add(_Rooms[i].GetName());
	}

	return result;
}

//Returns the names of all the unvisited rooms in the labyrinth.
//Used for the king's special skill.
StringList* Labyrinth::GetAllUnvisitedRoomNames()
{
	StringList* result = new StringList();

	for (int i = 0; i < _RoomCount; i++)
	{
		if (_Rooms[i].IsVisited() == false)
		{
			result->Add(_Rooms[i].GetName());
		}		
	}
	return result;
}

//Changes the current location to a random location
//Used for the minotaur's special skill.
void Labyrinth::MoveToRandom()
{
	//Random place, excluding the start and end node
	short newLocation = (rand() % (_RoomCount - 2))+1;
	_CurrentRoom = &_Rooms[newLocation];
	_NumberOfSteps++;
}

//Returns the number of taken steps, for statistics.
int Labyrinth::GetStatNumberOfSteps()
{
	return _NumberOfSteps;
}

//Returns the number of visited rooms, for statistics
int Labyrinth::GetStatNumberOfVisitedRooms()
{
	short counter = 0;
	for (int i = 0; i < _RoomCount; i++)
	{
		if (_Rooms[i].IsVisited() == true)
		{
			counter++;
		}
	}
	return counter;
}

//returns the (rounded) percentage of the explored labyrinth, for statistics
int Labyrinth::GetStatPercentageExplored()
{
	return (float)((float)GetStatNumberOfVisitedRooms() / (float)(_RoomCount-1)) * 100;
}


Labyrinth::~Labyrinth()
{
	delete[] _Rooms;
	delete[] _StrLabyrinth;
}
