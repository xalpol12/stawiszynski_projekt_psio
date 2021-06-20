#pragma once
#include "CreditsWindow.h"
class SettingsWindow : public CreditsWindow
{
private:
	std::map<std::string, std::string> text;
	std::map<std::string, MenuBox*>panels;
	std::map<std::string, MenuBox*>images;

	std::string selectedMap;

	void initImages();
	void initPanels();
	void initVariables();
public:
	SettingsWindow();
	~SettingsWindow();

	//Accessors
	std::string getSelectedMap();

	void updateCollision();
	void update();
	void render();
};

