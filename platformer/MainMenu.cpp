#include "stdafx.h"
#include "MainMenu.h"

void MainMenu::initAudio()
{
	this->songFilePath = "Music/menu_whole.ogg";
	this->music = new SongPlayer(songFilePath, 10, true);
}

void MainMenu::playAudio()
{
	this->music->playMusic();
}

void MainMenu::stopAudio()
{
	this->music->stopMusic();
}

void MainMenu::createBoxes()
{	
	this->menus["PLAY"] = new MenuBox(windowSize.x-2*this->marginX, windowSize.y/boxCount - this->marginY, this->marginX, this->marginY,"Play", this->font, 20);
	this->menus["HIGHSCORE"] = new MenuBox(windowSize.x - 2 * this->marginX, windowSize.y / boxCount - this->marginY, this->marginX, windowSize.y / boxCount + this->marginY, "High score", this->font, 20);
	this->menus["SETTINGS"] = new MenuBox(windowSize.x - 2 * this->marginX, windowSize.y / boxCount - this->marginY, this->marginX, 2 * windowSize.y / boxCount + this->marginY, "Settings", this->font, 20);
	this->menus["CREDITS"] = new MenuBox(windowSize.x - 2 * this->marginX, windowSize.y / boxCount - this->marginY, this->marginX, 3 * windowSize.y / boxCount + this->marginY, "Credits", this->font, 20);
}

void MainMenu::initVariables()
{
	this->clickedEscape = false;
	this->marginX = 100;
	this->marginY = 50;
	this->boxCount = 5;
	this->windowSize = {static_cast<float>(this->window.getSize().x), static_cast<float>(this->window.getSize().y) };
	this->loadFont();
	this->createBoxes();
	this->initAudio();
	this->playAudio();
}



MainMenu::MainMenu()
{
	this->initWindow("Main Menu");
	this->initVariables();
}

MainMenu::~MainMenu()
{
	for (auto it = menus.begin(); it != menus.end(); it++)
	{
		delete it->second;
	}
	delete this->music;
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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				it->second->changeTextColor(sf::Color::Color(90, 90, 90, 255));
				openSelected(it->first);
			}
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
		this->endState();
		this->stopAudio();
	}
	else if (selected_ == "HIGHSCORE")
	{
		this->openHighScoreWindow();
	}
	else if (selected_ == "SETTINGS")
	{
	}
	else
	{
		this->openCreditsWindow();
	}
}

void MainMenu::openHighScoreWindow()
{
	HighScoreWindow highScore;
	while (highScore.getWindow().isOpen())
	{
		highScore.update();
		highScore.render();
	}
}

void MainMenu::openOptionsWindow()
{
}

void MainMenu::openCreditsWindow()
{
	CreditsWindow creditsWindow;
	while(creditsWindow.getWindow().isOpen())
	{
		creditsWindow.update();
		creditsWindow.render();
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
