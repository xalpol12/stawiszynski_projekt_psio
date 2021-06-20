#include "stdafx.h"
#include "SettingsWindow.h"


void SettingsWindow::initImages()
{
	this->images["map1"] = new MenuBox(144.f, 91.f, marginX, 5 * marginY, "Txt/stage1.png");
	this->images["map2"] = new MenuBox(144.f, 91.f, 6.5*marginX, 5 * marginY, "Txt/stage2.png");
	this->images["map3"] = new MenuBox(144.f, 91.f, 12* marginX, 5 * marginY, "Txt/stage3.png");
}

void SettingsWindow::initPanels()
{
	this->panels["MAP"] = new MenuBox(panelHeight, panelWidth, windowSize.x-200.f, 2*marginY, text["MAP"], this->font, 20);
}

void SettingsWindow::initVariables()
{
	this->selectedMap = "map1"; //default map
	this->windowSize = { static_cast<float>(this->window.getSize().x), static_cast<float>(this->window.getSize().y) };
	this->file_name = "Txt/options.txt";
	this->panelCount = 4;
	this->panelHeight = windowSize.x / (panelCount * 4);
	this->panelWidth = windowSize.y / (panelCount * 4);
	this->marginX = 50.f;
	this->marginY = 50.f;
	this->loadFont();
	this->text = this->loadFromTxt(file_name);
	this->initPanels();
	this->initImages();
}

SettingsWindow::SettingsWindow()
{
	this->initWindow("Settings");
	this->initVariables();
}

SettingsWindow::~SettingsWindow()
{
	for (auto it = panels.begin(); it != panels.end(); it++)
	{
		delete it->second;
	}
	for (auto it = images.begin(); it != images.end(); it++)
	{
		delete it->second;
	}
}

std::string SettingsWindow::getSelectedMap()
{
	return this->selectedMap;
}

void SettingsWindow::updateCollision()
{
	for (auto it = images.begin(); it != images.end(); it++)
	{
		sf::FloatRect panelBounds = it->second->getPanelBounds();
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (mousePos.x > panelBounds.left &&
			mousePos.x < panelBounds.left + panelBounds.width &&
			mousePos.y > panelBounds.top &&
			mousePos.y < panelBounds.top + panelBounds.height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (selectedMap == it->first)
					continue;
				else 
				{
					this->selectedMap = it->first;
					std::cout << this->selectedMap << std::endl;
				}
			}
		}

		if(selectedMap == it->first)
			it->second->changeBoxColor(sf::Color::Red);
		else
			it->second->changeBoxColor(sf::Color::Transparent);
	}

}

void SettingsWindow::update()
{
	this->updatePollEvents();
	this->updateCollision();
}

void SettingsWindow::render()
{
	this->window.clear();

	for (auto it = panels.begin(); it != panels.end(); it++)
	{
		it->second->render(this->window);
	}

	for (auto it = images.begin(); it != images.end(); it++)
	{
		it->second->render(this->window);
	}

	this->window.display();
}
