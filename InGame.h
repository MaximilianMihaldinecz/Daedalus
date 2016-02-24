#pragma once
#include "ConsoleForm.h"
#include <string>
#include "StringList.h";

class InGame :
	public ConsoleForm
{
private:
	void DrawInGameScreen(short health, std::string roomName, std::string specialMsg, StringList* options, std::string specialSkill, std::string cursorString, bool DisplayReturnToMenu);
public:
	InGame();
	virtual int Draw();
	int Draw(short health, std::string roomName, std::string specialMsg, StringList* options, std::string specialSkill, std::string cursorString);
	int Draw(std::string specialMsg, std::string cursorString);
	int Draw(std::string specialMsg);
	int Draw(StringList* options, std::string title);
	
	static const std::string TextIntro;
	static const std::string TextIntroCursor;
	static const std::string TextEndCursor;
	static const std::string TextSpecialEndNode;
	static const std::string TextSpecialHealthUpNode;
	static const std::string TextSpecialHealthDownNode;
	static const std::string TextCharacterSkillMinotaur;
	static const std::string TextCharacterSkillKing;
	static const std::string TextCharacterSkillSorcerer;
	static const std::string TextMinotaurBerserk;
	static const std::string TextMinotaurBerserkCursor;
	static const std::string TextLostGame;
	static const std::string TextLostGameCursor;
	static const std::string TextMagicMapTitle;
	static const std::string TextWisdomTitle;

	~InGame();
};

