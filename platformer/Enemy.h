#pragma once
#include "EnemyUI.h"
namespace ENEMY_STATE
{
	enum ENEMY_ANIMATION_STATE { IDLE = 0, MOVING_LEFT = 1, MOVING_RIGHT = 2 };
}

class Enemy
{

protected:

	const sf::Texture* texture;
	sf::Sprite shape;
	sf::Vector2f direction;
	sf::Vector2f playerPos;
	sf::Vector2f position;
	sf::IntRect currentFrame;
	sf::Clock animationClock;
	float scalingFactor;
	short animState;

	EnemyUI* enemyUI;

	//Game variables
	int hp;
	int hpMax;
	int points;
	float speed;
	int damage;

	//Initialization
	void initUI();
	virtual void initTexture(sf::Texture* texture);

public:
	Enemy();
	virtual ~Enemy();

	//Accessors
	virtual const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;
	const int getPoints();
	const int getDamage();
	const int getHp();

	//Functions
	void subtractHp(const int& damage_);
	void restartClock();
	void normalizeVector();
	void resetVelocity();

	//Update
	virtual void updateMovement();
	virtual void updateAnimation() = 0;
	void update(sf::Vector2f playerPos_);

	//Render
	void render(sf::RenderTarget& target);
};

