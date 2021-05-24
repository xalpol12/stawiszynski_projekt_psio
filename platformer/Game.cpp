#include"stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1440,912), "Platformer", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(30);
}

void Game::initBackground()
{
	this->textures["BACKGROUND"] = new sf::Texture();
	this->textures["BACKGROUND"]->loadFromFile("Textures/Background.png");
	this->backgroundTexture.setTexture(*this->textures["BACKGROUND"]);
}

void Game::initPlayer()
{
	this->player = new Player();
	shootingTimer.restart();
}

void Game::initTileMap()
{
	this->map = new TileMap(this->textures["TILES"], this->window.getSize(), this->mapFilePath);
}

void Game::initTextures()
{
	this->mapFilePath = "Textures/map.txt";
	this->textures["PLAYER_BULLET1"] = new sf::Texture();					//Bullets
	this->textures["PLAYER_BULLET1"]->loadFromFile("Textures/bullet1.png");
	this->textures["ENEMY1"] = new sf::Texture();							//Enemy fire
	this->textures["ENEMY1"]->loadFromFile("Textures/EnemyFire.png");
	this->textures["TILES"] = new sf::Texture();
	this->textures["TILES"]->loadFromFile("Textures/tiles1.png");
}

Game::Game()
{
	this->initWindow();
	this->initBackground();
	this->initTextures();
	this->initPlayer();
	this->initTileMap();
}

Game::~Game()
{
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Deleting bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Deleting enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}

	////Delete tiles
	//for (auto* i : this->tiles)
	//{
	//	delete i;
	//}
}

sf::Texture* Game::getTexture(std::string texture_)
{
	return textures[texture_];
}

void Game::spawnEnemies()
{
	//TODO ADD SPAWN TIMER AND SPAWN POINTS
	
}

void Game::updateDeltaTime()
{
	this->deltaTime = this->clock.restart().asMilliseconds();
}

void Game::updatePollEvents()
{
	//Polling window events
	while (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window.close();
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			this->window.close();

		//Reseting animation
		if (this->event.type == sf::Event::KeyReleased &&
			((this->event.key.code == sf::Keyboard::A) ||
				(this->event.key.code == sf::Keyboard::D) ||
				(this->event.key.code == sf::Keyboard::W) ||
				(this->event.key.code == sf::Keyboard::S) ||
				(this->event.key.code == sf::Keyboard::Space)))
			this->player->resetAnimationTimer();

		//Shooting events
		accTimer += this->deltaTime;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && accTimer > 500.f)
		{
			accTimer = 0.f;
			this->bullets.push_back(new Bullet(this->textures["PLAYER_BULLET1"], this->player->calcPosition(this->window), this->player->getGlobalBounds()));
		}

		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			this->player->resetShooting();

		//Spawning enemy on click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			this->enemies.push_back(new Enemy_Fire(this->textures["ENEMY1"], sf::Vector2f(sf::Mouse::getPosition(window))));
			std::cout << enemies.size() << std::endl;
		}
	}
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
{
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)	//Collision bottom of screen
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, this->window.getSize().y - this->player->getGlobalBounds().height); 
		this->player->resetJumping();
	}
	if (this->player->getPosition().y < 0.f)	//Collision top of screen
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 0.f);
		this->player->resetJumping();
	}
	if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->window.getSize().x)	//Collision right wall
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->window.getSize().x - this->player->getGlobalBounds().width, this->player->getPosition().y); 
		this->player->resetJumping();
	}
	if (this->player->getPosition().x < 0.f)	//Collision left wall
	{
		this->player->resetVelocityY();
		this->player->setPosition(0.f, this->player->getPosition().y);
	}

	this->map->updatePlayerCollision(this->player);
}

void Game::updateCombat()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		//Enemy collision
		for (size_t k = 0; k < enemies.size(); k++)
		{
			if (bullets[i]->getBounds().intersects(enemies[k]->getBounds()))
			{
				this->points += enemies[k]->getPoints();
				std::cout << this->points << std::endl;
				bullets.erase(bullets.begin() + i);
				enemies.erase(enemies.begin() + k);

				break;
			}
		}
	}
}

void Game::updateEnemies()
{
	for (unsigned i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(this->player->getPosition());
		//Out of bounds enemies
		if (enemies[i]->getPosition().x <0 || enemies[i]->getPosition().x > window.getSize().x
			|| enemies[i]->getPosition().y < 0 || enemies[i]->getPosition().y > window.getSize().y)
		{
			enemies.erase(enemies.begin() + i);
		}
	}
	
}
void Game::updateBullets()
{
	for (unsigned i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update(this->deltaTime);

		//Out of bounds bullets
		if (bullets[i]->getPosition().x <0 || bullets[i]->getPosition().x > window.getSize().x
			|| bullets[i]->getPosition().y < 0 || bullets[i]->getPosition().y > window.getSize().y)
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			//Bullets colliding with tiles
			if (this->map->updateBulletCollision(this->bullets[i]))
			{
				bullets.erase(bullets.begin() + i); //TODO fix crashing ghost bullets -> vector out of range problem
				break;
			}
		}
	}
}

void Game::update()
{
	this->updateDeltaTime();
	this->updatePollEvents();
	this->updatePlayer();
	this->updateCollision();
	this->updateCombat();
	this->updateEnemies();
	this->updateBullets();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderWorld()
{
	this->window.draw(this->backgroundTexture);
}



void Game::render()
{
	this->window.clear();

	//Rendering background
	this->renderWorld();

	//Rendering Tile Map
	this->map->render(this->window);

	//Rendering player
	this->renderPlayer();


	//Rendering bullets
	for (size_t i = 0; i<bullets.size(); i++)
	{
		bullets[i]->render(this->window);
	}

	//Rendering enemies
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(this->window);
	}



	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}



