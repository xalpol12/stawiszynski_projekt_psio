#include "stdafx.h"
#include "CreditsWindow.h"

void CreditsWindow::loadFromTxt()
{
	int numberOfLines = 0;
	std::string line;
	std::ifstream in_file;
	std::string lineBefore;

	in_file.open(file_name);		//counting number of lines
	while (std::getline(in_file, line))
		numberOfLines++;
	in_file.close();

	in_file.open(file_name);
	if (in_file.is_open())
	{
		for (int i = 0; i < numberOfLines; i++)
		{
			std::getline(in_file, line);
			if (i % 2 == 0)
			{
				this->text[line];
			}
			else
			{
				this->text[lineBefore] = line;
			}
			lineBefore = line;
		}
		in_file.close();
	}
}

void CreditsWindow::initPanels()
{
	int counter = 0;
	for (auto it = text.begin(); it != text.end(); it++)
	{
		counter++;
		this->panels[it->first] = new MenuBox(panelHeight, panelWidth, marginX, counter *marginY, it->second, this->font, 20);
	}
}

void CreditsWindow::initVariables()
{
	this->windowSize = { static_cast<float>(this->window.getSize().x), static_cast<float>(this->window.getSize().y) };
	this->file_name = "Txt/credits.txt";
	this->panelCount = 4; //TODO - set to dynamic size
	this->panelHeight = windowSize.x / (panelCount * 2);
	this->panelWidth =  windowSize.y / (panelCount * 2);
	this->marginX = 100;
	this->marginY = 50;
	this->loadFont();
	this->loadFromTxt();
	this->initPanels();
}

CreditsWindow::CreditsWindow()
{
	this->initWindow("Credits");
	this->initVariables();
}

CreditsWindow::~CreditsWindow()
{
	for (auto it = panels.begin(); it != panels.end(); it++)
	{
		delete it->second;
	}
}

void CreditsWindow::update()
{
	this->updatePollEvents();
}

void CreditsWindow::render()
{
	this->window.clear();

	for (auto it = panels.begin(); it != panels.end(); it++)
	{
		it->second->render(this->window);
	}

	this->window.display();
}
