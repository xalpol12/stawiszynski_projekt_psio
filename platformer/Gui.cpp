#include "stdafx.h"
#include "Gui.h"

void Gui::initVariables()
{
	this->pointTextPos = sf::Vector2f(1280.f, 10.f);
	this->gameOverTextPos = sf::Vector2f(570.f, 430.f);
	this->characterSize = 20;
	this->hpBarSize = sf::Vector2f(300.f, 25.f);
	this->counter = 0;
	this->maxCounter = 255;
}

void Gui::loadFont()
{
	if (!this->font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
}

void Gui::initPointText()
{
	this->pointText.setPosition(this->pointTextPos);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(this->characterSize);
	this->pointText.setFillColor(sf::Color::White);
}

void Gui::initGameOverText()
{
	this->gameOverText.setPosition(this->gameOverTextPos);
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(this->characterSize * 3);
	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setString("Game over");
}

void Gui::initGameOverRectangle()
{
	this->gameOverShape.setSize(sf::Vector2f(1440.f, 912.f));
	this->gameOverShape.setPosition(sf::Vector2f(0.f, 0.f));
	this->gameOverShape.setFillColor(sf::Color::Color(0, 0, 0, 255));
}

void Gui::initPlayerHpBar()
{
	this->playerHpBar.setSize(sf::Vector2f(this->hpBarSize));
	this->playerHpBar.setFillColor(sf::Color::Red);

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Gui::initElements()
{
	this->initVariables();
	this->loadFont();
	this->initPointText();
	this->initGameOverText();
	this->initGameOverRectangle();
	this->initPlayerHpBar();
}

Gui::Gui()
{
	this->initElements();
}

Gui::~Gui()
{
	delete this;
}

void Gui::updatePointText(int points_)
{
	std::stringstream ss;
	ss << "Points: " << points_;
	this->pointText.setString(ss.str());
}

void Gui::updatePlayerHpBar(int hp_, int hpMax_)
{
	float hpPercent = static_cast<float>(hp_) / hpMax_;
	this->playerHpBar.setSize(sf::Vector2f(this->hpBarSize.x * hpPercent, this->hpBarSize.y));
}


void Gui::update(int points_, int hp_, int hpMax_ )
{
	this->updatePointText(points_);
	this->updatePlayerHpBar(hp_, hpMax_);
}

void Gui::animateGameOverRectangle(int counter_)
{
	this->gameOverShape.setFillColor(sf::Color::Color(0, 0, 0, 0 + counter_));
}

void Gui::animateGameOverText(int counter_)
{
	this->gameOverText.setFillColor(sf::Color::Color(255, 255, 255, 0 + counter));
}

void Gui::updateGameOver()
{
	if (this->counter < this->maxCounter)
		this->counter+=5;
	this->animateGameOverRectangle(counter);
	this->animateGameOverText(counter);
}

void Gui::render(sf::RenderTarget& target)
{
	target.draw(this->pointText);
	target.draw(this->playerHpBarBack);
	target.draw(this->playerHpBar);
}

void Gui::renderGameOver(sf::RenderTarget& target)
{
	target.draw(this->gameOverShape);
	target.draw(this->gameOverText);
}
