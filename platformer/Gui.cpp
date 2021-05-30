#include "stdafx.h"
#include "Gui.h"

void Gui::initVariables()
{
	this->pointTextPos = sf::Vector2f(1280.f, 10.f);
	this->characterSize = 20;
	this->hpBarSize = sf::Vector2f(300.f, 25.f);
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

void Gui::render(sf::RenderTarget& target)
{
	target.draw(this->pointText);
	target.draw(this->playerHpBarBack);
	target.draw(this->playerHpBar);
}
