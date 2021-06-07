#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{ 
	this->hpMax = 100;
	this->hp = this->hpMax;
	this->damage = 5;
	this->attackSpeed = 0.f;
	this->attackSpeedMax = 600.f;

	this->animState = PLAYER_ANIMATION_STATE::IDLE;
	this->scalingFactor = 3;
	this->isShooting = false;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/PlayerSheet.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet" << "\n";
	}
}

float Player::calcShootingOrientation()
{
	float playerX = this->getPosition().x;
	float cursorX = sf::Mouse::getPosition(*this->window).x;
	return cursorX - playerX;
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->sprite.setScale(scalingFactor, scalingFactor);
	this->currentFrame = sf::IntRect(4, 21, 25, 24);
	this->sprite.setTextureRect(this->currentFrame);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->isJumping = false;
	this->velocityMax = 20.f;
	this->velocityMin = 1.f;
	this->acceleration = 4.f;
	this->drag = 0.85f;
	this->gravity = 6.f;
	this->velocityMaxY = 20.f;
}

Player::Player(sf::Window* window_)
{
	this->window = window_;
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{
}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;
	this->velocity.y += dir_y * 25*this->acceleration; 

	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}


void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.5 * this->gravity;
	//if (std::abs(this->velocity.y) > this->velocityMaxY)
	//{
	//	this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	//}

	//Deceleration
	this->velocity *= this->drag;

	//Limit deceleration (stopping movement)
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}


void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATE::IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //RIGHT
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_RIGHT;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !this->isJumping) //Jump
	{
		this->move(0.f, -1.f);
		this->animState = PLAYER_ANIMATION_STATE::JUMPING;
		this->isJumping = true;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->isShooting = true;
	}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //DOWN
	//{
	//	this->move(0.f, 1.f);
	//}
}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

sf::Vector2f Player::calcPosition(sf::Window& window_)
{
	sf::Vector2f playerCenter = sf::Vector2f(this->getPosition().x, this->getPosition().y);
	sf::Vector2f mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window_));
	sf::Vector2f aimDir = mousePosWindow - playerCenter;
	sf::Vector2f aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2.f) + pow(aimDir.y, 2.f));
	return aimDirNorm;
}


void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}


const sf::Vector2i Player::getGridPosition(int gridSizeI_) const
{
	return sf::Vector2i(static_cast<int>(this->sprite.getPosition().x)/gridSizeI_,
						static_cast<int>(this->sprite.getPosition().y)/gridSizeI_);
}

const sf::Vector2f Player::getVelocity() const
{
	return this->velocity;
}

void Player::resetShooting()
{
	this->isShooting = false;
}

const int Player::getHp()
{
	return this->hp;
}

const int Player::getHpMax()
{
	return this->hpMax;
}

const int Player::getDamage()
{
	return this->damage;
}

void Player::resetJumping()
{
	this->isJumping = false;
}

bool Player::isOpposite()
{
	return false;
}

void Player::loseHp(int damage_)
{
	if (this->hp > 0)
		this->hp -= damage_;
}

void Player::addHp(int value_)
{
	if(this->hp+value_ <= this->hpMax)
	this->hp += value_;
}

void Player::addHpMax(int value_)
{
	this->hpMax += value_;
}

void Player::addDamage(int value_)
{
	this->damage += value_;
}

void Player::addShootingSpeed(int value_)
{
	if(this->attackSpeed<this->attackSpeedMax)
	this->attackSpeed += value_;
}


void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

const float Player::getAttackSpeed()
{
	return this->attackSpeed;
}


void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::updateAnimations()
{

	if (this->animState == PLAYER_ANIMATION_STATE::IDLE && isShooting)	//Idle and shooting
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.01f || this->getAnimSwitch())
		{
			this->currentFrame.top = 78;
			this->currentFrame.left = 3;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		if (this->calcShootingOrientation() < 0.f)
		{
			this->sprite.setScale(scalingFactor, scalingFactor);
			this->sprite.setOrigin(0.f, 0.f);
		}
		else
		{
			this->sprite.setScale(-scalingFactor, scalingFactor);
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / scalingFactor, 0.f);
		}

	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_LEFT && isShooting)  //Running left and shooting
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 78;
			this->currentFrame.left += 32;
			if (this->currentFrame.left >= 134 || this->currentFrame.left < 38)
				this->currentFrame.left = 38;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(scalingFactor, scalingFactor);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_RIGHT && isShooting)  //Running left and shooting
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 78;
			this->currentFrame.left += 32;
			if (this->currentFrame.left >= 134 || this->currentFrame.left < 38)
				this->currentFrame.left = 38;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-scalingFactor, scalingFactor);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / scalingFactor, 0.f);
	}

	if (this->animState == PLAYER_ANIMATION_STATE::IDLE)				//Idle
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 21;
			//this->currentFrame.left += 25;
			//if (this->currentFrame.left >= 50)
			this->currentFrame.left = 4;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_LEFT)	//Running left
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 21;
			this->currentFrame.left += 25;
			if (this->currentFrame.left >= 160 || this->currentFrame.left < 90)
				this->currentFrame.left = 90;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(scalingFactor, scalingFactor);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_RIGHT)	//Running right
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 21;
			this->currentFrame.left += 25;
			if (this->currentFrame.left >= 165 || this->currentFrame.left < 90)
				this->currentFrame.left = 90;
			this->sprite.setTextureRect(this->currentFrame);
			this->animationTimer.restart();
		}
		this->sprite.setScale(-scalingFactor, scalingFactor);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / scalingFactor, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::JUMPING)	//Jumping
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 13;
			this->currentFrame.left = 174;
			this->sprite.setTextureRect(this->currentFrame);
			this->animationTimer.restart();
		}
		this->sprite.setScale(scalingFactor, scalingFactor);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else
		animationTimer.restart();
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}




void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}


