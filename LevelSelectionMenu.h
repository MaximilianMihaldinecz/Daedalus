#pragma once
#include "ConsoleForm.h"
class LevelSelectionMenu :
	public ConsoleForm
{
private:
	void DrawLevelSelectionScreen();
public:
	LevelSelectionMenu();
	int Draw();
	~LevelSelectionMenu();
};

