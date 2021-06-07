#include "stdafx.h"
#include "Enemy.h"

void Enemy::initUI()
{
	this->enemyUI = new EnemyUI(this->getBounds(),5.f,60.f);
}

void Enemy::initTexture(sf::Texture* texture)
{
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	this->enemyUI->damageAnimation(hp, this->getPosition());
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

const int Enemy::getDamage()
{
	return this->damage;
}

const int Enemy::getHp()
{
	return this->hp;
}

void Enemy::subtractHp(const int& damage_)
{
	this->hp -= damage_;
	this->enemyUI->damageAnimation(damage_, this->getPosition());
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
	this->enemyUI->update(this->hp, this->hpMax, this->getPosition());
	this->updateAnimation();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	this->enemyUI->render(target);
}
