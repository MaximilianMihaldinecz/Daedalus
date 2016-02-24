#pragma once
#include "MainMenu.h"
#include "LevelSelectionMenu.h"
#include "PlayerSelectionMenu.h"
#include "Labyrinth.h"
#include "Player.h";
#include "FileMenu.h"

class MainFlow
{
private:
	MainMenu _MainMenu;
	PlayerSelectionMenu _PlayerSelectionMenu;
	LevelSelectionMenu _LevelSelectionMenu;
	Player *_CurrentGame;
	FileMenu _FileMenu;

	void NewGame(int player, Labyrinth* labyrinth);
	void HandleMainMenu();
	int NewGameLauncher(int player, int level);
	int LoadGameLauncher(int player);
	int SaveCurrentLauncher();
	bool SaveCurrent(std::string filename);
	Labyrinth* GetNewLabyrinth(short numberOfRooms, short maxNodes);
	Labyrinth* LoadFromFileLabyrinth(std::string location);

public:
	MainFlow();
	int Launch();
	~MainFlow();
};

