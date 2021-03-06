#include "stdafx.h"
#include "Bullet.h"


sf::Vector2f Bullet::calcArmPosition()
{
	sf::Vector2f pos;
	pos.x = this->center.left + 25.f;
	pos.y = this->center.top + 40.f;
		return pos;
}

void Bullet::initVariables()
{
	this->initialSpeed = 1.5f;
}


Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, sf::Vector2f direction_, sf::FloatRect center_)
{
	this->initVariables();
	this->shape.setTexture(*texture);
	this->direction = direction_;
	this->center = center_;
	this->shape.setPosition(this->calcArmPosition());
	this->shape.scale(2.5f, 2.5f);
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const sf::Vector2f Bullet::getPosition() const
{
	return this->shape.getPosition();
}

const sf::Vector2i Bullet::getGridPosition(int gridSizeI_) const
{
	return sf::Vector2i(static_cast<int>(this->shape.getPosition().x) / gridSizeI_,
		static_cast<int>(this->shape.getPosition().y) / gridSizeI_);
}

void Bullet::resetVelocity()
{
	this->initialSpeed = 0.f;
}

void Bullet::update(float deltaTime_)
{
	this->shape.move(this->direction * this->initialSpeed * deltaTime_);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
