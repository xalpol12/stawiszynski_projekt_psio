#pragma once
#include "CreditsWindow.h"
class HighScoreWindow: public CreditsWindow
{
private:
	std::map<int, std::string> text;
	std::map<int, MenuBox*> panels;

	void loadFromTxt();
	void initPanels();
	void initVariables();
public:
	HighScoreWindow();
	~HighScoreWindow();

	void update();
	void render();
};

