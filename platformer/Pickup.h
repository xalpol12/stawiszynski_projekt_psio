#pragma once
#include "Player.h"

class Pickup
{
private:
	sf::Sprite shape;
	sf::IntRect currentFrame;
	float animationTimer;
	float scalingFactor;
	int type;  // 0 = 
	int value;

	//Movement
	float velocityY;
	float velocityMaxY;
	float gravity;
	bool stopMovement;

	void initItemType(std::string name_);
	void initVariables(sf::Texture* texture_, sf::IntRect texturePos_, std::string name_, sf::Vector2f pos_, int value_);
public:
	Pickup(sf::Texture* texture_, sf::IntRect texturePos_, std::string name_, sf::Vector2f pos_, int value_);
	~Pickup();

	//Modifiers
	void resetVelocityY();

	//Accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2i getGridPosition(int gridSize_) const;
	const float getVelocity() const;

	//Functions
	void setPosition(sf::Vector2f pos_);
	void execute(Player& player_);

	void updatePhysics(float deltaTime_);
	void updateAnimations(float deltaTime_);
	void update(float deltaTime_);
	void render(sf::RenderTarget& target);
};

