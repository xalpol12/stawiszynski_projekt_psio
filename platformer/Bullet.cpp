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
	this->initialSpeed = 60.f;
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
	this->shape.scale(2.f, 2.f);
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

void Bullet::update()
{
	this->shape.move(this->direction * this->initialSpeed);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
