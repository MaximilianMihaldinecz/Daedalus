#pragma once
#include<string>

class LabyrinthGenerator
{
private:
	short** GenerateRelationMatrix(short nodes, short maxlinks);
	short NumberOfEmptySpace(short *arr, short length);
	bool Contains(short *arr, short length, short value);
	bool Contains(std::string *arr, short length, std::string& value);
	void InsertToFreeSpace(short *arr, short length, short value);
	std::string* GenerateRoomNames(short nodes);
	unsigned char* GenerateRoomTypes(short nodes);
	std::string* RelationMatrixToString(short nodes, short** rMatrix, short maxlinks);
	std::string* RoomTypesToString(short nodes, unsigned char* rTypes);
public:
	LabyrinthGenerator();
	std::string* Generate(short nodeCount, short maxLinks);
	~LabyrinthGenerator();
};

