#pragma once
#include<string>
#include"StringList.h"

class FileManager
{
private:
	short _LoadedRowCount;
	StringList* _LoadedFile;

public:
	FileManager();
	bool IsValidFileNameToLoad(std::string fn);
	bool IsValidFileNameToSave(std::string fn);
	bool Load(std::string fn);
	std::string* GetFile();
	short GetLoadedRowCount();
	bool Save(std::string* strLabyrinth, short rowCount, std::string fn);
	~FileManager();
};

