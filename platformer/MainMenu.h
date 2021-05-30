#pragma once
#include "MenuBox.h"

class MainMenu
{
private:
	sf::Vector2f windowSize;
	sf::RenderWindow window;
	sf::Event event;
	sf::Font font;
	std::map<std::string, MenuBox*> menus;
	MenuBox* test;

	int marginX, marginY;
	int boxCount;
	bool isSelected;

	void loadFont();
	void createBoxes();

	void initVariables();
	void initWindow();
public:
	MainMenu();
	~MainMenu();

	//Functions
	void endState();

	//Updates
	void updatePollEvents();
	void updateCollision();
	void openSelected(std::string selected_);

	void update();
	void render();
	const sf::RenderWindow& getWindow() const;
};

