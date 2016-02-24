#pragma warning(disable : 4996)
#include "FileManager.h"
#include<string>
#include<fstream>
#include<iostream>
#include"StringList.h"

using namespace std;

FileManager::FileManager()
{
	_LoadedRowCount = 0;
	_LoadedFile = NULL;
}

//Returns true if the given filename is a valid 
//filename for saving
bool FileManager::IsValidFileNameToSave(string fn)
{
	bool result = false;
	if (FILE *file = fopen(fn.c_str(), "w")) {
		fclose(file);
		return true;
	}
	return result;
}

//Returns true if the given filename is an existing
//file with read permission
bool FileManager::IsValidFileNameToLoad(string fn)
{
	bool result = false;
	if (FILE *file = fopen(fn.c_str(), "r")) {
		fclose(file);
		return true;
	}
	return result;
}

//Returns the number of rows from the loaded file
short FileManager::GetLoadedRowCount()
{
	return _LoadedRowCount;
}

//Saves the given array of strings to the given file name
bool FileManager::Save(string* strLabyrinth, short rowCount, string fn)
{
	bool result = false;
	if (IsValidFileNameToSave(fn) == true)
	{
		ofstream file;
		file.open(fn);
		for (short i = 0; i < rowCount; i++)
		{
			file << strLabyrinth[i];
			if (i < rowCount - 1)
			{
				file << "\n";
			}
		}
		file.close();
		result = true;
	}
	return result;
}

//Reads the content of a file from the given location
//Returns true if there was no error during the process.
bool FileManager::Load(string fn)
{
	bool result = false;
	
	if (IsValidFileNameToLoad(fn) == true)
	{
		if (_LoadedFile != NULL)
		{
			delete _LoadedFile;
		}

		_LoadedRowCount = 0;
		ifstream file;
		file.open(fn);

		_LoadedFile = new StringList();
		string temp;
				
		while (getline(file, temp))
		{
			_LoadedFile->Add(temp);
			_LoadedRowCount++;
		}

		file.close();
		result = true;
	}

	return result;
}

//Returns the array of string containing the file loaded previously
string* FileManager::GetFile()
{
	if (_LoadedFile->GetCount() > 0)
	{
		return _LoadedFile->GetAll();
	}
	else
	{
		return NULL;
	}	
}

FileManager::~FileManager()
{
}
