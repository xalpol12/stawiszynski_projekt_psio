#include "stdafx.h"
#include "SubMenu.h"

void SubMenu::initWindow(std::string title_)
{
	this->window.create(sf::VideoMode(800, 600), title_, sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(30);
}

void SubMenu::loadFont()
{
	if (!this->font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
}

void SubMenu::initVariables()
{
	this->clickedEscape = false;
	this->loadFont();
}

SubMenu::SubMenu()
{
	this->initWindow("emptystring");
	this->initVariables();
}

SubMenu::~SubMenu()
{
}

void SubMenu::endState()
{
	this->window.close();
}

bool SubMenu::wasEscapePressed()
{
	return this->clickedEscape;
}

void SubMenu::updatePollEvents()
{
	while (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			clickedEscape = true;
			std::cout << "SWITCH bool" << std::endl;
			this->window.close();
		}
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
		{
			this->window.close();
		}
	}
}

void SubMenu::update()
{
	this->updatePollEvents();
}

void SubMenu::render()
{
	this->window.clear();
	this->window.display();
}

const sf::RenderWindow& SubMenu::getWindow() const
{
	return this->window;
}