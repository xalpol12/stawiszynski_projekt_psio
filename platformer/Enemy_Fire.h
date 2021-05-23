#pragma once
#include "Enemy.h"


class Enemy_Fire : public Enemy
{
private:
	void initVariables();
	void initTexture(sf::Texture* texture);
public:

	//Constructors
	Enemy_Fire(sf::Texture* texture_, sf::Vector2f spawnLocation);
	~Enemy_Fire();

	//Update
	void updateAnimation();
};

