#include "MainFlow.h"
#include "MainMenu.h"
#include "LevelSelectionMenu.h"
#include "PlayerSelectionMenu.h"
#include "LabyrinthGenerator.h"
#include "Labyrinth.h"
#include "FileManager.h"
#include<string>
#include "Minotaur.h"
#include "Sorcerer.h"
#include "King.h"
#include<exception>
#include "FileMenu.h"

using namespace std;

//Static allocation of the program-wise used View layer objects for the main menus.
MainFlow::MainFlow()
{
	_MainMenu = MainMenu();
	_PlayerSelectionMenu = PlayerSelectionMenu();
	_LevelSelectionMenu = LevelSelectionMenu();
	_FileMenu = FileMenu();
	_CurrentGame = NULL;
}


MainFlow::~MainFlow()
{
}

//Instantiates a LabyrinthGenerator object and generates a labyrinth.
Labyrinth* MainFlow::GetNewLabyrinth(short numberOfRooms, short maxNodes)
{
	LabyrinthGenerator *generator = new LabyrinthGenerator();
	string* strLabyrinth = generator->Generate(numberOfRooms, maxNodes);
	Labyrinth* labyrinth = new Labyrinth(strLabyrinth, numberOfRooms);
	delete generator;
	return labyrinth;
}

//Instantiates a FileManager and saves the current labyrinth to the disk
bool MainFlow::SaveCurrent(string filename)
{
	bool result = false;
	FileManager *fm = new FileManager();

	try
	{
		short length = _CurrentGame->GetLabyrinthLength();
		string* labAsString = _CurrentGame->GetLabyrinthAsString();
		result = fm->Save(labAsString, length, filename);		
	} catch (exception& e) {}


	delete fm;
	return result;
}

//Saves the labyrinth in the _CurrentGame to the disk.
//Displays the save file menu.
int MainFlow::SaveCurrentLauncher()
{
	int result = NULL;
	string filename = "";
	bool showError = false;
	bool success = false;

	//Get filename and try to save the labyrinth
	while (filename != "0" && success == false)
	{
		filename = _FileMenu.Draw(false, showError);
		success = SaveCurrent(filename);
		if (success == false)
		{
			showError = true;
		}
	}

	if (success == true)
	{
		_FileMenu.ConfirmSave();
	}

	return result;
}

//Instantiates a FileManager object and tries to load the labyrinth file from the disk
Labyrinth* MainFlow::LoadFromFileLabyrinth(string location)
{
	Labyrinth* labyrinth = NULL;
	FileManager *fm = new FileManager();

	try
	{
		if (fm->Load(location))
		{
			short rowCount = fm->GetLoadedRowCount();
			string *fileContent = fm->GetFile();
			labyrinth = new Labyrinth(fileContent, rowCount);
		}
	}
	catch (exception& e) {}
	
	delete fm;
	return labyrinth;
}

//Instantiates the appropiate subclass of the play class as the current game
void MainFlow::NewGame(int player, Labyrinth* labyrinth)
{
	switch (player)
	{
	case 1:
		_CurrentGame = new Sorcerer(labyrinth);
		break;
	case 2:
		_CurrentGame = new King(labyrinth);
		break;
	case 3:
		_CurrentGame = new Minotaur(labyrinth);
		break;
	default:
		_CurrentGame = new Minotaur(labyrinth);
		break;
	}
}

//Gets a labyrinth from file and launches the game
//with the selected player. Displays the load file menu.
int MainFlow::LoadGameLauncher(int player)
{
	int result = NULL;
	string filename = "";
	Labyrinth *labyrinth = NULL;
	bool showError = false;

	//Get Labyrinth filename and try to generate the labyrinth
	while (filename != "0" && labyrinth == NULL)
	{
		filename = _FileMenu.Draw(true, showError);
		labyrinth = LoadFromFileLabyrinth(filename);
		if (labyrinth == NULL)
		{
			showError = true;
		}
	}

	//If have the labyrinth, launch the game
	if (labyrinth != NULL)
	{
		//First delete the current game if exists
		if (_CurrentGame != NULL)
		{
			delete _CurrentGame;
		}

		//Create the player (controller) object
		NewGame(player, labyrinth);

		//Launch the game
		result = _CurrentGame->StartGame();
	}

	return result;
}

//Gets a newly generated labyrinth and launches the game
//with the selected player.
int MainFlow::NewGameLauncher(int player, int level)
{
	int result = NULL;
	
	//Generate new Labyrinth
	Labyrinth* labyrinth;
	switch (level)
	{
	case 1:
		labyrinth = GetNewLabyrinth(10, 5);
		break;
	case 2:
		labyrinth = GetNewLabyrinth(20, 8);
		break;
	case 3:
		labyrinth = GetNewLabyrinth(30, 10);
		break;
	case 4:
		labyrinth = GetNewLabyrinth(40, 10);
		break;
	case 5:
		labyrinth = GetNewLabyrinth(1000, 12);
		break;
	default:
		labyrinth = GetNewLabyrinth(100, 10);
		break;
	}

	//Create the player (controller) object
	NewGame(player, labyrinth);

	//Starting the game
	result = _CurrentGame->StartGame();

	return result;
}

void MainFlow::HandleMainMenu()
{
	int response = 0;
	int playerSelected = 0;
	int levelSelected = 0;
	do 
	{
		//Draw the main menu and get the user input. If there is an ongoing game, offer save option too.
		if (_CurrentGame == NULL)
		{
			response = _MainMenu.Draw();
		}
		else
		{
			response = _MainMenu.Draw(true);
		}
		
		
		//"New game" selected in the main menu by the user
		if (response == 1)
		{
			//Draw the player type selection menu
			playerSelected = _PlayerSelectionMenu.Draw();
			
			//The player did not select the "Return to main" option
			if (playerSelected != 0)
			{
				//Draw the difficulty level selection menu
				levelSelected = _LevelSelectionMenu.Draw();

				//The player did not select the "Return to main" option
				if (levelSelected != 0)
				{					
					//Start a new game, but first delete the existing one if there is
					if (_CurrentGame != NULL)
					{
						delete _CurrentGame;
					}
					//Launch the new game
					NewGameLauncher(playerSelected, levelSelected);
				}
			}
		}

		//"Load from file" selected in the main menu by the user
		if (response == 2)
		{
			//Draw the player type selection menu
			playerSelected = _PlayerSelectionMenu.Draw();

			//The player did not select the "Return to main" option
			if (playerSelected != 0)
			{
				LoadGameLauncher(playerSelected);
			}
		}

		//"Save to file" selected in the main menu by the user
		if (response == 3)
		{
			SaveCurrentLauncher();
		}

	} while (response);
	//Breaks out when user selected the "Exit" option (option 0)
}

int MainFlow::Launch()
{	
	HandleMainMenu();	
	return 0;
}
