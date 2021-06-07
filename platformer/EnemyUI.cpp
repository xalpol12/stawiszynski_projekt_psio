#include "stdafx.h"
#include "EnemyUI.h"

void EnemyUI::initVariables()
{
	this->hpTextPos = sf::Vector2f(100.f, 0.f);
	this->characterSize = 14;
	this->hpBarSize = sf::Vector2f(enemyDimensions.width+ 10.f , 15.f);
}

void EnemyUI::initDamageText()
{
	this->damageText.setFont(this->font);
	this->damageText.setCharacterSize(this->characterSize+4);
}

void EnemyUI::initElements()
{
	this->initVariables();
	this->loadFont();
	this->initHpText();
	this->initHpBar();
	this->initDamageText();
}


EnemyUI::EnemyUI(const sf::FloatRect& size_, const float& offsetX_, const float& offsetY_)
{
	this->offsetX = offsetX_;
	this->offsetY = offsetY_;
	this->enemyDimensions = size_;
	this->initElements();
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::damageAnimation(int damage_, sf::Vector2f pos_)
{
	this->damageText.setString("-" + std::to_string(damage_));
	this->damageText.setPosition(pos_);
	sf::Uint8 transparency = 255;
}


void EnemyUI::updateHpText(const int& hp_, const int& hpMax_, const sf::Vector2f& pos_)
{
	this->hpText.setPosition(pos_.x - offsetX + 10.f, pos_.y + offsetY-2.f);
	this->hpText.setString(std::to_string(hp_) + "/" + std::to_string(hpMax_));
}

void EnemyUI::updateHpBar(const int& hp_, const int& hpMax_, const sf::Vector2f& pos_)
{
	float hpPercent = static_cast<float>(hp_) / hpMax_;
	this->HpBar.setSize(sf::Vector2f(this->hpBarSize.x * hpPercent, this->hpBarSize.y));
	this->HpBar.setPosition(pos_.x-offsetX,pos_.y+offsetY);
	this->HpBarBack.setPosition(pos_.x-offsetX, pos_.y + offsetY);
}

void EnemyUI::updateDamageText()
{
	transparency -= 20;
	if (transparency >= 0)
		this->damageText.setFillColor(sf::Color::Color(255, 255, 255, 0));
	else
		this->damageText.setFillColor(sf::Color::Transparent);
}

void EnemyUI::update(const int& hp_, const int& hpMax_, const sf::Vector2f& pos_)
{
	this->updateHpText(hp_, hpMax_, pos_);
	this->updateHpBar(hp_, hpMax_, pos_);
	this->updateDamageText();
}


void EnemyUI::render(sf::RenderTarget& target)
{
	target.draw(this->HpBarBack);
	target.draw(this->HpBar);
	target.draw(this->hpText);
	target.draw(this->damageText);
}


