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

public:
	//Init
	void initVariables();

	Bullet();
	Bullet(sf::Texture* texture, sf::Vector2f direction_, sf::FloatRect center_);
	~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;

	void update();
	void render(sf::RenderTarget& target);
};

