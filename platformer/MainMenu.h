#pragma once
#include "MenuBox.h"
#include "SubMenu.h"
#include "CreditsWindow.h"
#include "HighScoreWindow.h"

class MainMenu : public SubMenu
{
private:
	sf::Vector2f windowSize;
	std::map<std::string, MenuBox*> menus;

	int marginX, marginY;
	int boxCount;


	void createBoxes();
	void initVariables();

public:
	MainMenu();
	~MainMenu();

	//Updates
	void updateCollision();
	void openSelected(std::string selected_);

	//Submenus
	void openHighScoreWindow();
	void openOptionsWindow();
	void openCreditsWindow();


	void update();
	void render();
	const sf::RenderWindow& getWindow() const;
};

