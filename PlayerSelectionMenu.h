#pragma once
#include "ConsoleForm.h"
class PlayerSelectionMenu :
	public ConsoleForm
{
private:
	void DrawPlayerSelectionScreen();

public:
	PlayerSelectionMenu();
	int Draw();
	~PlayerSelectionMenu();
};

