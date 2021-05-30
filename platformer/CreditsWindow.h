#pragma once
#include "SubMenu.h"
#include "MenuBox.h"
class CreditsWindow : public SubMenu
{
private:
	std::map<std::string, std::string> text;
	std::map<std::string, MenuBox*> panels;

protected:
	sf::Vector2f windowSize;
	std::string file_name;


	float panelHeight, panelWidth;
	int marginX, marginY;
	int panelCount;

	void loadFromTxt();
	void initPanels();
	void initVariables();
public:
	CreditsWindow();
	~CreditsWindow();

	void update();
	void render();
};

