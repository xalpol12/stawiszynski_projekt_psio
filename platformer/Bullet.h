#pragma once
class Bullet
{
private:
	sf::Sprite shape;
	sf::Vector2f direction;
	sf::FloatRect center;
	float initialSpeed;

	//Calculations
	sf::Vector2f calcArmPosition();

	//Init
	void initVariables();

public:


	Bullet();
	Bullet(sf::Texture* texture, sf::Vector2f direction_, sf::FloatRect center_);
	~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;
	const sf::Vector2i getGridPosition(int gridSizeI_) const;

	//Functions
	void resetVelocity();

	void update(float deltaTime_);
	void render(sf::RenderTarget& target);
};

