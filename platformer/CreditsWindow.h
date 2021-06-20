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
	float marginX, marginY;
	int panelCount;

	std::map<std::string,std::string> loadFromTxt(std::string file_name_);
	void initPanels();
	void initVariables();
public:
	CreditsWindow();
	~CreditsWindow();

	void update();
	void render();
};

