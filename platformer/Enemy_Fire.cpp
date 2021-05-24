#include "stdafx.h"
#include "Enemy_Fire.h"

void Enemy_Fire::initVariables()
{
	this->playerPos.x = 10.f;		//Needed nonzero value for first iteration of updateMovement()
	this->playerPos.y = 10.f;		// with shape.move() function taking nonzero value
	this->scalingFactor = 3;
	this->animState = ENEMY_STATE::ENEMY_ANIMATION_STATE::IDLE;
	this->points = 10;
	this->speed = 7.f;
	this->damage = 10;
}

void Enemy_Fire::initTexture(sf::Texture* texture_)
{
	this->texture = texture_;
	this->shape.setTexture(*texture);
	this->currentFrame = sf::IntRect(0, 0, 17, 16);
	this->shape.setTextureRect(this->currentFrame);
	this->shape.setScale(scalingFactor, scalingFactor);
	this->animationClock.restart();
}

Enemy_Fire::Enemy_Fire(sf::Texture* texture_, sf::Vector2f spawnLocation)
{
	this->initVariables();
	this->initTexture(texture_);
	this->shape.setPosition(spawnLocation);
	this->update(playerPos);
}

Enemy_Fire::~Enemy_Fire()
{
}

void Enemy_Fire::updateAnimation()
{
	if (this->animState == ENEMY_STATE::ENEMY_ANIMATION_STATE::IDLE)
	{
		if (this->animationClock.getElapsedTime().asSeconds() > 2.f)
		{
			this->currentFrame.left = 0;
			this->currentFrame.height = 0;
			this->restartClock();
			this->shape.setTextureRect(this->currentFrame);
		}
		this->shape.setScale(scalingFactor, scalingFactor);
		this->shape.setOrigin(0.f, 0.f);
	}
	else if (this->animState == ENEMY_STATE::ENEMY_ANIMATION_STATE::MOVING_LEFT)
	{
		if (this->animationClock.getElapsedTime().asSeconds() > 0.2f)
		{
			this->currentFrame.left += 16;
			if (this->currentFrame.left >= 30)
				this->currentFrame.left = 0;
			this->restartClock();
			this->shape.setTextureRect(this->currentFrame);
		}
		this->shape.setScale(-scalingFactor, scalingFactor);
		this->shape.setOrigin(this->shape.getGlobalBounds().width / scalingFactor, 0.f);
	}
	else if (this->animState == ENEMY_STATE::ENEMY_ANIMATION_STATE::MOVING_RIGHT)
	{
		if (this->animationClock.getElapsedTime().asSeconds() > 0.2f)
		{
			this->currentFrame.left += 16;
			if (this->currentFrame.left >= 30)
				this->currentFrame.left = 0;
			this->restartClock();
			this->shape.setTextureRect(this->currentFrame);
		}
		this->shape.setScale(scalingFactor, scalingFactor);
		this->shape.setOrigin(0.f, 0.f);
	}
	else
		this->restartClock();
}

