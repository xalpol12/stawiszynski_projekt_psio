#pragma once
namespace ENEMY_STATE
{
	enum ENEMY_ANIMATION_STATE { IDLE = 0, MOVING_LEFT = 1, MOVING_RIGHT = 2 };
}

class Enemy_Fire
{
private:
	//Animation and texture variables
	const sf::Texture* texture;
	sf::Sprite shape;
	sf::Vector2f direction;
	sf::Vector2f playerPos;
	sf::Vector2f position;
	sf::IntRect currentFrame;
	sf::Clock animationClock;
	float scalingFactor;
	short animState;

	//Game variables
	int points;
	float speed;
	int damage;

	//Initialization
	void initVariables();
	void initTexture(sf::Texture* texture);

public:


	//Constructors
	Enemy_Fire();
	Enemy_Fire(sf::Texture* texture_, sf::Vector2f spawnLocation);
	~Enemy_Fire();

	//Accessors
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;

	//Functions
	void restartClock();

	//Update
	void updateMovement();
	void updateAnimation();
	void update(sf::Vector2f playerPos_);

	//Render
	void render(sf::RenderTarget& target);
};

