#include "stdafx.h"
#include "MainMenu.h"

void MainMenu::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Main Menu", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(30);
}

void MainMenu::loadFont()
{
	if (!this->font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
}

void MainMenu::createBoxes()
{	
	this->menus["PLAY"] = new MenuBox(windowSize.x-2*this->marginX, windowSize.y/boxCount - this->marginY, this->marginX, this->marginY,"Play", this->font);
	this->menus["HIGHSCORE"] = new MenuBox(windowSize.x - 2 * this->marginX, windowSize.y / boxCount - this->marginY, this->marginX, windowSize.y / boxCount + this->marginY, "High score", this->font);
	this->menus["SETTINGS"] = new MenuBox(windowSize.x - 2 * this->marginX, windowSize.y / boxCount - this->marginY, this->marginX, 2 * windowSize.y / boxCount + this->marginY, "Settings", this->font);
	this->menus["CREDITS"] = new MenuBox(windowSize.x - 2 * this->marginX, windowSize.y / boxCount - this->marginY, this->marginX, 3 * windowSize.y / boxCount + this->marginY, "Credits", this->font);
}

void MainMenu::initVariables()
{
	this->isSelected = false;
	this->marginX = 100;
	this->marginY = 50;
	this->boxCount = 5;
	this->windowSize = {static_cast<float>(this->window.getSize().x), static_cast<float>(this->window.getSize().y) };
	this->loadFont();
	this->createBoxes();
}



MainMenu::MainMenu()
{
	this->initWindow();
	this->initVariables();

}

MainMenu::~MainMenu()
{
	for (auto it = menus.begin(); it != menus.end(); it++)
	{
		delete it->second;
	}
}

void MainMenu::endState()
{
}

void MainMenu::updatePollEvents()
{
	while (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window.close();
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			this->window.close();
	}
}

void MainMenu::updateCollision()
{
	for (auto it = menus.begin(); it != menus.end(); it++)
	{
		sf::FloatRect panelBounds = it->second->getPanelBounds();
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (mousePos.x > panelBounds.left &&
			mousePos.x < panelBounds.left + panelBounds.width &&
			mousePos.y > panelBounds.top &&
			mousePos.y < panelBounds.top + panelBounds.height)
		{
			it->second->changeTextColor(sf::Color::Color(150, 150, 150, 255));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!isSelected)
			{
				it->second->changeTextColor(sf::Color::Color(90, 90, 90, 255));
				openSelected(it->first);
				this->isSelected = true;
			}
			std::cout << "Inside" << std::endl;
		}
		else
		{
			it->second->changeTextColor(sf::Color::Color::White);
		}
	}
}

void MainMenu::openSelected(std::string selected_)
{
	if (selected_ == "PLAY")
	{
		std::cout << "PLAY SELECTED" << std::endl;
	}
	else if (selected_ == "HIGHSCORE")
	{
	}
	else if (selected_ == "SETTINGS")
	{
	}
	else
	{
	}
}

void MainMenu::update()
{
	this->updatePollEvents();
	this->updateCollision();
}

void MainMenu::render()
{
	this->window.clear();

	for (auto it = menus.begin(); it!= menus.end(); it++)
	{
		it->second->render(this->window);
	}

	this->window.display();
}

const sf::RenderWindow& MainMenu::getWindow() const
{
	return this->window;
}
