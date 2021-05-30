#pragma once

enum PLAYER_ANIMATION_STATE {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING, SHOOTING};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	float scalingFactor;
	sf::Clock animationTimer;
	sf::Window* window;

	//Animation
	short animState;
	sf::IntRect currentFrame;		//Rectangle 21x24     1 - 3x21, 2 - 24x21, 3 - 24x45, 4 - 3x45 
									//				Punkt 1 - x,y;   2 - x+21, y; 3 - x+21, y+24;  4 - x, y+21	
	bool animationSwitch;
	float calcShootingOrientation();

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//Gameplay variables
	int hp;
	int hpMax;

	//Bools
	bool isJumping;
	bool isShooting;

	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player(sf::Window* window);
	~Player();


	//Accessor
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getVelocity() const;
	const sf::Vector2i getGridPosition(int gridSizeI_) const;
	const int getHp();
	const int getHpMax();

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityX();
	void resetVelocityY();
	void resetJumping();
	void resetShooting();
	void resetAnimationTimer();
	void loseHp(int damage_);

	//Functions
	void move(const float dir_x, const float dir_y);
	sf::Vector2f calcPosition(sf::Window& window_);
	bool isOpposite();
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

