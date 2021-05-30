#include "stdafx.h"
#include "HighScoreWindow.h"

void HighScoreWindow::loadFromTxt()
{
	int numberOfLines = 0;
	std::string line;
	std::ifstream in_file;
	std::string lineBefore;
	std::vector<int> allEntries;

	in_file.open(file_name); //reading number of entries
	while (std::getline(in_file, line))
		numberOfLines++;
	in_file.close();

	in_file.open(file_name);
	if (in_file.is_open())
	{
		for (int i = 0; i < numberOfLines; i++)
		{
			std::getline(in_file, line);
			int score = std::stoi(line);
			allEntries.push_back(score);
		}

		std::sort(allEntries.rbegin(), allEntries.rend());

		for (int i = 0; i < numberOfLines && i < 10; i++)
		{
			this->text[i+1];
			this->text[i+1] = std::to_string(allEntries[i]);
		}
		in_file.close();
	}
}

void HighScoreWindow::initPanels()
{
	for (auto it = text.begin(); it != text.end(); it++)
	{
		this->panels[it->first] = new MenuBox(panelHeight, panelWidth, marginX, it->first * marginY,
			std::to_string(it->first) + ". " + it->second, this->font, 20);
	}
}

void HighScoreWindow::initVariables()
{
	this->windowSize = { static_cast<float>(this->window.getSize().x), static_cast<float>(this->window.getSize().y) };
	this->file_name = "Txt/highscore.txt";
	this->panelCount = 10;
	this->panelHeight = windowSize.x / panelCount;
	this->panelWidth = windowSize.y / panelCount;
	this->marginX = 100;
	this->marginY = 50;
	this->loadFont();
	this->loadFromTxt();
	this->initPanels();
}

HighScoreWindow::HighScoreWindow()
{
	this->initWindow("High Score");
	this->initVariables();
}

HighScoreWindow::~HighScoreWindow()
{
	for (auto it = panels.begin(); it != panels.end(); it++)
	{
		delete it->second;
	}
}

void HighScoreWindow::update()
{
	this->updatePollEvents();
}

void HighScoreWindow::render()
{
	this->window.clear();

	for (auto it = panels.begin(); it != panels.end(); it++)
	{
		it->second->render(this->window);
	}

	this->window.display();
}
