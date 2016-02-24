#include "LabyrinthGenerator.h"
#include "Room.h"
#include<string>
#include<time.h>

using namespace std;

LabyrinthGenerator::LabyrinthGenerator()
{
}

//Counts the number of empty spaces in an array of shorts
//Empty spaces represented as -1 values
short LabyrinthGenerator::NumberOfEmptySpace(short *arr, short length)
{
	short counter = 0;
	for (short i = 0; i < length; i++)
	{
		if (arr[i] == -1)
		{
			counter++;
		}
	}
	return counter;
}

//Returns true if the given array of shorts contains the specified value
bool LabyrinthGenerator::Contains(short *arr, short length, short value)
{
	bool result = false;
	for (short i = 0; i < length; i++)
	{
		if (arr[i] == value)
		{
			result = true;
			break;
		}
	}
	return result;
}

//Returns true if the given array of strings contains the specified value
bool LabyrinthGenerator::Contains(string *arr, short length, string& value)
{
	bool result = false;
	for (short i = 0; i < length; i++)
	{
		if (arr[i] == value)
		{
			result = true;
			break;
		}
	}
	return result;
}

//Inserts the given value into a free space in the given array of shorts
//Free spaces represented as -1 values
void LabyrinthGenerator::InsertToFreeSpace(short *arr, short length, short value)
{
	for (short i = 0; i < length; i++)
	{
		if (arr[i] == -1)
		{
			arr[i] = value;
			break;
		}
	}
}

//Returns a matrix of shorts containing the nodes and their links
short** LabyrinthGenerator::GenerateRelationMatrix(short nodes, short maxlinks)
{
	//Creating an array of pointers to point to arrays of shorts
	short **matrix = new short*[nodes];

	//Creating arrays of shorts
	for (short i = 0; i < nodes; i++)
	{
		matrix[i] = new short[maxlinks];
	}

	//Setting up default values to -1
	for (short i = 0; i < nodes; i++)
	{
		for (short j = 0; j < maxlinks; j++)
		{
			matrix[i][j] = -1;
		}
	}

	//Creating a valid route between the start and end by connecting the nodes linearly
	matrix[0][0] = 1;
	matrix[nodes - 1][0] = nodes - 2;
	for (short i = 1; i < nodes - 1; i++)
	{
		matrix[i][0] = i - 1;
		matrix[i][1] = i + 1;
	}

	//Generating valid random links
	for (short i = 0; i < (nodes - 1); i++)
	{
		//Does the actual node has still space for more nodes, preserve one space empty for potential back-linking
		short freeSpaces = NumberOfEmptySpace(matrix[i], maxlinks);
		if (freeSpaces > 1)
		{
			//How many new links should be added (random)
			short numberOfNewLinks = rand() % (freeSpaces - 1);
			//Storing the found new links in this array
			short *newLinks = new short[numberOfNewLinks];

			//Giving a default value for the newLinks elements
			for (short x = 0; x < numberOfNewLinks; x++)
			{
				newLinks[x] = -1;
			}


			//Finding nodes that can have valid links with
			short potential;
			short j = 0;
			while (j < numberOfNewLinks)
			{
				//Select a random node, excluding the end node
				potential = rand() % (nodes - 1);

				//Not the same node as where we are
				if (potential != i)
				{
					//The potential also has a space for a (back)link 
					if (NumberOfEmptySpace(matrix[i], maxlinks) > 0)
					{
						//If the potential node is not already in the list (prevent duplicates)
						if (Contains(matrix[i], maxlinks, potential) == false)
						{
							//If this potential has not been selected already in a previous iteration
							if (Contains(newLinks, numberOfNewLinks, potential) == false)
							{
								//Valid node, add to the list
								newLinks[j] = potential;
								j++;
							}
						}
					}
				}
			}

			//Copy in the new links to the matrix
			if (numberOfNewLinks > 0)
			{
				for (short h = 0; h < numberOfNewLinks; h++)
				{
					//Create the link
					InsertToFreeSpace(matrix[i], maxlinks, newLinks[h]);
					//Create the back-link
					InsertToFreeSpace(matrix[newLinks[h]], maxlinks, i);
				}
			}

			//Free up memory
			delete[] newLinks;

		}
	}


		return matrix;
}


//Returns an array of strings containing random, unique room names
string* LabyrinthGenerator::GenerateRoomNames(short nodes)
{
	const short emotionsCount = 48;
	const string emotions[emotionsCount] = { "Anger", "Annoyance", "Contempt", "Disgust", "Irritation", "Anxiety", "Embarrassment", "Fear", "Helplessness", "Powerlessness", "Worry", "Doubt", "Envy", "Frustration", "Guilt", "Shame", "Boredom", "Despair", "Disappointment", "Hurt", "Sadness", "Stress", "Shock", "Tension", "Amusement", "Delight", "Elation", "Excitement", "Happiness", "Joy", "Pleasure", "Affection", "Empathy", "Friendliness", "Love", "Courage", "Hope", "Pride", "Satisfaction", "Trust", "Calmness", "Contentment", "Relaxation", "Relief", "Serenity", "Interest", "Politeness", "Surprise" };
	const short nounsCount = 9;
	const string nouns[nounsCount] = { "Room", "Hall", "Chamber", "Lair", "Den", "Tunnel", "Haunt", "Pit", "Hollow" };
	const short coloursCount = 10;
	const string colours[coloursCount] = { "Black", "Blue", "Red", "Green", "Pink", "Yellow", "Brown", "Gold", "Silver", "Bronze" };
	
	string *roomNames = new string[nodes];
	for (int i = 0; i < nodes; i++)
	{
		roomNames[i] = "";
	}

	short fewRooms = 100;
	short manyRooms = 1000;

	if (nodes <= fewRooms)
	{
		//Generate short room names as "Room name" + "of" + "Emotion name"
		string temp;
		short i = 0;		
		while (i < nodes)
		{
			temp = nouns[rand() % nounsCount] + " of " + emotions[rand() % emotionsCount];
			if (Contains(roomNames, nodes, temp) == false)
			{
				roomNames[i] = temp;
				i++;
			}
		}
	}
	else if (nodes <= manyRooms)
	{
		//Generate long room names as "Colour name" + "Room name" + "of" + "Emotion name"
		string temp;
		short i = 0;
		while (i < nodes)
		{
			temp = colours[rand() % coloursCount] + " " + nouns[rand() % nounsCount] + " of " + emotions[rand() % emotionsCount];
			if (Contains(roomNames, nodes, temp) == false)
			{
				roomNames[i] = temp;
				i++;
			}
		}
	}
	else
	{
		//Generate very long room names as "Colour name" + "Room name" + "of" + "Emotion name" + "and" + "Emotion name"
		string temp;
		short i = 0;
		while (i < nodes)
		{
			temp = colours[rand() % coloursCount] + " " + nouns[rand() % nounsCount] + " of " + emotions[rand() % emotionsCount] + " and " + emotions[rand() % emotionsCount];
			if (Contains(roomNames, nodes, temp) == false)
			{
				roomNames[i] = temp;
				i++;
			}
		}
	}

	return roomNames;
}

//Returns an array of unsigned chars, containing room types (numbers 0-4)
unsigned char* LabyrinthGenerator::GenerateRoomTypes(short nodes)
{
	unsigned char *roomTypes = new unsigned char[nodes];
	const unsigned char startNode = 0;
	const unsigned char endNode = 1;
	const unsigned char regularNode = 2;
	const unsigned char addHealthNode = 3;
	const unsigned char removeHealthNode = 4;

	//Setting up the start and end node
	roomTypes[0] = startNode;
	roomTypes[nodes - 1] = endNode;

	//Setting up the rest of the nodes to regular nodes
	for (short i = 1; i < nodes - 1; i++)
	{
		roomTypes[i] = regularNode;
	}

	//Adding an addHealthNode to half way of the route
	roomTypes[nodes / 2] = addHealthNode;

	//Adding a removeHealthNode at about 75% of the route
	//If only a few nodes available, then place it just after addHealthNode
	if (nodes > 9)
	{
		roomTypes[(nodes * 3)/4] = removeHealthNode;
	}
	else
	{
		roomTypes[(nodes / 2) + 1] = removeHealthNode;
	}

	return roomTypes;
}

//Converts the array of unsigned char room types into array of strings 
string* LabyrinthGenerator::RoomTypesToString(short nodes, unsigned char* rTypes)
{
	string* RoomTypes = new string[nodes];
	for (short i = 0; i < nodes; i++)
	{
		RoomTypes[i] = to_string(rTypes[i]);
	}
	return RoomTypes;
}

//Converts the relation matrix into an array of strings
string* LabyrinthGenerator::RelationMatrixToString(short nodes, short** rMatrix, short maxlinks)
{
	string* relations = new string[nodes];
	for (short i = 0; i < nodes; i++)
	{
		relations[i] = "";
		for (short j = 0; j < maxlinks; j++)
		{
			//If the value is not -1 (which represents "no link") then add to the string
			if (rMatrix[i][j] != -1)
			{
				if (j > 0)
				{
					relations[i] += "," + to_string(rMatrix[i][j]);
				}
				else
				{
					//Don't add comma before the first element
					relations[i] += to_string(rMatrix[i][j]);
				}				
			}
		}
	}
	return relations;
}


//Generates a random labyrinth with the give amount of rooms and
// maximum number of links per rooms. Minimum number of nodes should be 5.
string* LabyrinthGenerator::Generate(short nodeCount, short maxLinks)
{
	string* newLabyrinth = NULL;
	unsigned char* roomTypes = NULL;
	string* strRoomTypes = NULL;
	string* roomNames = NULL;
	short** relationMatrix = NULL;
	string* strRelationMatrix = NULL;

	//Number of maximum connections between nodes
	const short maxlinks = maxLinks;

	//Minimum number of nodes in a graph must be 5
	if (nodeCount < 5)
	{
		return NULL;
	}

	//Init newLabyrinth
	newLabyrinth = new string[nodeCount];

	//Salting the random number generator
	srand(time(0));

	//Generating data
	roomTypes = GenerateRoomTypes(nodeCount);
	roomNames = GenerateRoomNames(nodeCount);
	relationMatrix = GenerateRelationMatrix(nodeCount, maxlinks);

	//Converting into string format
	strRoomTypes = RoomTypesToString(nodeCount, roomTypes);
	strRelationMatrix = RelationMatrixToString(nodeCount, relationMatrix, maxlinks);

	//Concatenate into the final result
	for (short i = 0; i < nodeCount; i++)
	{
		newLabyrinth[i] = strRoomTypes[i] + "," + roomNames[i] + "," + strRelationMatrix[i];
	}

	//Freeing up memory
	delete[] roomTypes;
	delete[] strRoomTypes;
	delete[] roomNames;
	delete[] strRelationMatrix;
	for (short i = 0; i < nodeCount; i++)
	{
		delete [] relationMatrix[i];
	}
	delete[] relationMatrix;

	//return result as an array of strings
	return newLabyrinth;
}

LabyrinthGenerator::~LabyrinthGenerator()
{
}
