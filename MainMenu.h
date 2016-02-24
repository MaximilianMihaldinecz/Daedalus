#pragma once
#include<string>
#include "ConsoleForm.h"

class MainMenu : public ConsoleForm
{
private:

void DrawGameInfo();
void DrawMainScreen(std::string* options, int length);

public:
	MainMenu();
	int Draw();
	int Draw(bool hasSave);
	~MainMenu();
};

