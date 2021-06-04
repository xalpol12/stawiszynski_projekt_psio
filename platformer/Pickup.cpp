#include "stdafx.h"
#include "Pickup.h"

void Pickup::initItemType(std::string name_)
{
	if (name_ == "HEAL")
		this->type = 0;
	if (name_ == "HP_UP")
		this->type = 1;
}

void Pickup::initVariables(sf::Texture* texture_, sf::IntRect texturePos_, std::string name_, sf::Vector2f pos_, int value_)
{
	this->animationTimer = 0.f;
	this->value = value_;
	this->initItemType(name_);

	//Textures
	this->shape.setTexture(*texture_);
	this->scalingFactor = 4;
	this->shape.setScale(scalingFactor, scalingFactor);
	this->currentFrame = texturePos_;
	this->shape.setTextureRect(currentFrame);

	//Physics
	this->stopMovement = false;
	this->velocityY = 0.f;
	this->velocityMaxY = 20.f;
	this->gravity = 0.05f;
	this->shape.setPosition(pos_);
}

Pickup::Pickup(sf::Texture* texture_, sf::IntRect texturePos_, std::string name_, sf::Vector2f pos_, int value_)
{
	this->initVariables(texture_, texturePos_, name_, pos_, value_);
}

Pickup::~Pickup()
{
}

void Pickup::resetVelocityY()
{
	this->velocityY = 0.f;
	this->stopMovement = true;
}

const sf::FloatRect Pickup::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const sf::Vector2i Pickup::getGridPosition(int gridSize_) const
{
	return sf::Vector2i(static_cast<int>(this->shape.getPosition().x) / gridSize_,
			static_cast<int>(this->shape.getPosition().y) / gridSize_);
}

const float Pickup::getVelocity() const
{
	return this->velocityY;
}

void Pickup::setPosition(sf::Vector2f pos_)
{
	this->shape.setPosition(pos_);
}

void Pickup::execute(Player& player_)
{
	switch (type)
	{
	case 0: player_.addHp(this->value);
		break;

	case 1: player_.addHpMax(this->value);
		break;
	}
}

void Pickup::updatePhysics(float deltaTime_)
{ 
	if (!stopMovement)
	{
		if (this->velocityY < this->velocityMaxY)
			this->velocityY += this->gravity*deltaTime_;
		std::cout << this->velocityY << std::endl;
	}

	this->shape.move(0.f, this->velocityY);
}

void Pickup::updateAnimations(float deltaTime_)
{
	this->animationTimer = animationTimer + deltaTime_;
	if (this->animationTimer > 15*deltaTime_)
	{
		this->animationTimer = 0.f;
		this->currentFrame.top += 8.f;
		if (this->currentFrame.top >= 16.f)
			this->currentFrame.top = 0.f;
		this->shape.setTextureRect(this->currentFrame);
	}

}

void Pickup::update(float deltaTime_)
{
	this->updatePhysics(deltaTime_);
	this->updateAnimations(deltaTime_);
}

void Pickup::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
