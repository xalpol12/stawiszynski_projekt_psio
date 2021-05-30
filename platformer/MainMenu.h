#pragma once
#include "MenuBox.h"
#include "SubMenu.h"
#include "CreditsWindow.h"
#include "HighScoreWindow.h"
#include "SongPlayer.h"

class MainMenu : public SubMenu
{
private:
	sf::Vector2f windowSize;
	std::map<std::string, MenuBox*> menus;
	SongPlayer* music;

	int marginX, marginY;
	int boxCount;
	bool clickedEscape;
	std::string songFilePath;

	void initAudio();
	void playAudio();
	void stopAudio();
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

