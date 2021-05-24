#include "stdafx.h"
#include "Enemy.h"

void Enemy::initTexture(sf::Texture* texture)
{
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const sf::Vector2f Enemy::getPosition() const
{
	return this->shape.getPosition();
}

const int Enemy::getPoints()
{
	return this->points;
}

void Enemy::restartClock()
{ 
	this->animationClock.restart();
}

void Enemy::normalizeVector()
{
		//Normalize vector
	this->direction = this->playerPos - this->position;
	float hyp = sqrt(pow(this->direction.x, 2.f) + pow(this->direction.y, 2.f));
	this->direction = direction / hyp;
}

void Enemy::resetVelocity()
{
	this->speed = 0.f;
}

void Enemy::updateMovement()
{
	this->normalizeVector();

	//TODO - proximity check
	this->shape.move(speed * direction.x, direction.y * 0.5f * speed);

	if (this->direction.x > 0)
		this->animState = ENEMY_STATE::ENEMY_ANIMATION_STATE::MOVING_LEFT;
	else
		this->animState = ENEMY_STATE::ENEMY_ANIMATION_STATE::MOVING_RIGHT;
	this->position = this->getPosition();
}

void Enemy::update(sf::Vector2f playerPos_)
{
	this->playerPos = playerPos_;
	this->updateMovement();
	this->updateAnimation();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
