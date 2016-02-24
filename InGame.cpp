#include "InGame.h"
#include<ostream>
#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>

using namespace std;


const string InGame::TextIntro = "You wake up in a labyrinth.\nYou must find your way out before you starve to death.";
const string InGame::TextIntroCursor = "Press 0 and hit Enter to start: ";
const string InGame::TextEndCursor = "Press 0 and hit Enter to return to the main menu: ";
const string InGame::TextSpecialEndNode = "You have found the exit! Congratulation!";
const string InGame::TextSpecialHealthUpNode = "You found food in this room. Your health goes up!";
const string InGame::TextSpecialHealthDownNode = "This room was very cold. You lost some health :(.";
const string InGame::TextCharacterSkillMinotaur = "Go berserk.";
const string InGame::TextCharacterSkillKing = "Was I here already?";
const string InGame::TextCharacterSkillSorcerer = "Show magical map.";
const string InGame::TextMinotaurBerserk = "The mad Minotaur went Berserk!\nYou were running through multiple rooms unconsciously...\n...and you find yourself in a random place.";
const string InGame::TextMinotaurBerserkCursor = "Press 0 and hit Enter to continue: ";
const string InGame::TextLostGame = "Your health has depleted. You lost in Daedalus' great labyrinth.\nGame over!";
const string InGame::TextLostGameCursor = "Press 0 and hit Enter to return to the main menu: ";
const string InGame::TextMagicMapTitle = "~~~~~ You summon your magical map... follow the rooms in ascending order ~~~~~";
const string InGame::TextWisdomTitle = "~~~~~ You recalling your memories... You have not been in these rooms: ~~~~~";


InGame::InGame()
{
}

//Draws the user interface while playing the game.
//Displays the users health, the current room name, special message of the room,
//the list of options, the character's special skill, the text to display before the input cursor
//and potentially the return to main menu option.
void InGame::DrawInGameScreen(short health, string roomName, string specialMsg, StringList *options, string specialSkill, string cursorString, bool DisplayReturnToMenu)
{
	ClearScreen();

	//Displaying health
	if (health != NULL)
	{
		cout << "Your health: " << health << endl;
		cout << endl;
	}	

	//Displaying the room name, if exists
	if (roomName != "")
	{
		cout << "You have arrived to the " << roomName << endl;
	}
	
	//Displaying the special message, if exists
	if (specialMsg != "")
	{
		cout << specialMsg << endl;
	}

	//Displaying the list of rooms where player can move forward
	//Displaying the character's special skill as well
	if (options != NULL)
	{
		cout << endl;
		cout << "From here, you can move to these rooms (select a number):" << endl;
		short length = options->GetCount();
		for (short i = 0; i < length; i++)
		{
			cout << "    " << i + 2 << ".   " << options ->Get(i) <<endl;
		}

		//Displaying character specific skill
		if (specialSkill != "")
		{
			cout << endl;
			cout << "OR:" << endl;			
			cout << "    " << "1" << ".   " << "Use the character's special skill: " << specialSkill << endl;
		}
	}

	//Displaying the return to main menu option
	if (DisplayReturnToMenu == true)
	{
		
		cout << "    " << "0" << ".   " << "Return to the game's main menu." << endl;
	}

	//Moving to the input location. Displaying input expectations to the user.
	MoveCursor(20, 1);
	if (cursorString == "")
	{
		cout << "Enter your selection (a number): ";
	}
	else
	{
		cout << cursorString;
	}
	
}

//Not applicable
int InGame::Draw()
{
	return 0;
}

//Displays the current room 
int InGame::Draw(short health, std::string roomName, std::string specialMsg, StringList* options, std::string specialSkill, std::string cursorString)
{
	int selection = -1;
	int maxOptions = options->GetCount() +1;

	while (selection < 0 || selection > maxOptions)
	{
		DrawInGameScreen(health, roomName, specialMsg, options, specialSkill,cursorString,true);
		selection = GetSelection();
	}

	return selection;
}

//Displays only a special message and a cursor string. Used for intro screen.
int InGame::Draw(std::string specialMsg, std::string cursorString)
{
	int selection = -1;
	while (selection != 0 )
	{
		DrawInGameScreen(NULL, "", specialMsg, NULL, "", cursorString,false);
		selection = GetSelection();
	}

	return selection;
}

//Displays only a special message. 
int InGame::Draw(std::string specialMsg)
{
	int selection = -1;
	while (selection != 0)
	{
		DrawInGameScreen(NULL, "", specialMsg, NULL, "", "",false);
		selection = GetSelection();
	}
	return selection;
}

//Displays a title and a list of options
int InGame::Draw(StringList* options, string title)
{
	int selection = -1;
	short max = options->GetCount();
	ClearScreen();
	
	cout << title << endl << endl;
	for (int i = 0; i < max; i++)
	{
		cout << i << ". " << options->Get(i) << "    ";
	}

	cout << endl << endl;
	while (selection != 0)
	{
		cout << "Type 0 and press Enter to continue: ";
		selection = GetSelection();
	}

	return selection;
}


InGame::~InGame()
{
}
