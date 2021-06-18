#include"stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1440,912), "Platformer", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(30);
}

void Game::initVariables()
{
	this->points = 0;
	this->spawnTimer = 0.f;
	this->spawnTimerMax = 2000.f;
	this->musicSwitchState = 1;
	this->scoreFilePath = "Txt/highscore.txt";
	this->audioPath["MAINSONG1"] = "Music/mainsong2.ogg";
	this->audioPath["MAINSONG2"] = "Music/PapSmear.ogg";
	this->audioPath["ENDSONG"] = "Music/endscreen.ogg";

	this->audioPath["PLAYERDEATH"] = "Sounds/death_sound.ogg";
	this->audioPath["PLAYERHIT"] = "Sounds/hit_sound.ogg";
}

void Game::initBackground()
{
	this->textures["BACKGROUND"] = new sf::Texture();
	this->textures["BACKGROUND"]->loadFromFile("Textures/Background.png");
	this->backgroundTexture.setTexture(*this->textures["BACKGROUND"]);
}

void Game::initGui()
{
	this->gui = new Gui();
}

void Game::initMusic()
{
	this->songs.push_back(new SongPlayer(this->audioPath["MAINSONG1"], this->musicVol, false)); //TODO unmute songs before final release
	this->songs.push_back(new SongPlayer(this->audioPath["MAINSONG2"], 10, false));
	this->songs.push_back(new SongPlayer(this->audioPath["ENDSONG"], this->musicVol, true));
	this->playMainMusic();
}

void Game::initSounds()
{
	this->sounds.push_back(new SoundPlayer(this->audioPath["PLAYERDEATH"], this->soundVol));
	this->sounds.push_back(new SoundPlayer(this->audioPath["PLAYERHIT"], this->soundVol));
}

void Game::initPlayer()
{
	this->player = new Player(&this->window);
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
	this->textures["PICKUPS"] = new sf::Texture();
	this->textures["PICKUPS"]->loadFromFile("Textures/Pickups.png");
}

Game::Game(int musicVol_, int soundVol_)
{
	this->musicVol = musicVol_;
	this->soundVol = soundVol_;
	this->initVariables();
	this->initWindow();
	this->initBackground();
	this->initTextures();
	this->initGui();
	this->initMusic();
	this->initSounds();
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

	//Deleting pickups
	for (auto* i : this->pickups)
	{
		delete i;
	}

	delete this->textManager;

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
	int random = 0;
	this->spawnTimer += this->deltaTime;

	if (this->spawnTimer > this->spawnTimerMax)
	{
		this->spawnTimer = 0;
		random = rand() % 4;
		switch (random)		//random corner of the map
		{
			case 0: this->randomCorner = sf::Vector2f(10.f, 10.f); break;
			case 1: this->randomCorner = sf::Vector2f(10.f, window.getSize().y - 10.f); break;
			case 2: this->randomCorner = sf::Vector2f(window.getSize().x - 10.f, window.getSize().y - 10.f); break;
			case 3: this->randomCorner = sf::Vector2f(window.getSize().x - 10.f, 10.f); break;
		}
		this->enemies.push_back(new Enemy_Fire(this->textures["ENEMY1"], this->randomCorner));
	}
	
}

void Game::spawnPickup(const sf::Vector2f& pos_)
{
	int random = rand() & 3;
	switch (random)
	{
	case 0: 
		//this->pickups.push_back(new Pickup(this->textures["PICKUPS"], sf::IntRect(0, 0, 9, 8), "HEAL", pos_, 10));
		break;
	case 1:
		//this->pickups.push_back(new Pickup(this->textures["PICKUPS"], sf::IntRect(8, 0, 9, 8), "HP_UP", pos_, 5));
		break;
	case 2:
		//this->pickups.push_back(new Pickup(this->textures["PICKUPS"], sf::IntRect(17, 0, 9, 8), "DAMAGE", pos_, 1));
		break;
	case 3:
		this->pickups.push_back(new Pickup(this->textures["PICKUPS"], sf::IntRect(26, 0, 9, 8), "SHOOT_SPEED", pos_, 50));
		break;
	}
}

const int Game::getPlayerHp() const
{
	return this->player->getHp();
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

		int counter = 0;
		accTimer += this->deltaTime;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&accTimer>700.f-this->player->getAttackSpeed())
		{
				accTimer = 0.f;
				this->bullets.push_back(new Bullet(this->textures["PLAYER_BULLET1"], this->player->calcPosition(this->window), this->player->getGlobalBounds()));
		}

		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			this->player->resetShooting();

		//Spawning enemy on click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{

			//this->enemies.push_back(new Enemy_Fire(this->textures["ENEMY1"], sf::Vector2f(sf::Mouse::getPosition(window))));
			/*std::cout << enemies.size() << std::endl;*/
		}
	}
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateGui()
{
	this->gui->update(points, this->player->getHp(), this->player->getHpMax());
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
	for (size_t i = 0; i < bullets.size(); i++)
	{
		//Enemy collision
		for (size_t k = 0; k < enemies.size(); k++)
		{
			if (bullets[i]->getBounds().intersects(enemies[k]->getBounds()))
			{
				this->points += enemies[k]->getPoints();
				bullets.erase(bullets.begin() + i);
				if (this->enemies[k]->getHp() - this->player->getDamage() <= 0)
				{
					this->spawnPickup(enemies[k]->getPosition());
					enemies.erase(enemies.begin() + k);
				}
				else
				{
					this->enemies[k]->subtractHp(this->player->getDamage());
				}

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
		//Enemy - player collision
		else if (enemies[i]->getBounds().intersects(this->player->getGlobalBounds()))
		{
			if(this->player->getHp() - this->enemies[i]->getDamage()<= 0)
				this->sounds.at(0)->playSound();
			else 
				this->sounds.at(1)->playSound();
			this->player->loseHp(this->enemies[i]->getDamage());

			this->enemies.erase(enemies.begin() + i);
		}

		//Enemy - enemy collision
		//for (unsigned k = 0; k < enemies.size(); k++)
		//{
		//	if (enemies[i]->getBounds().intersects(enemies[k]->getBounds()))
		//	{
		//		enemies[k]->moveBy(10.f, 0.f);
		//		break;
		//	}
		//}
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

void Game::updatePickups()
{
	for (unsigned i = 0; i < pickups.size(); i++)
	{
		this->pickups[i]->update(this->deltaTime);
		this->map->updatePickupCollision(pickups[i]);
		if (this->pickups[i]->getGlobalBounds().intersects(this->player->getGlobalBounds()))
		{
			this->pickups[i]->execute(*player);
			pickups.erase(pickups.begin() + i);
		}
	}
}

#pragma region Playing_music

void Game::playMainMusic()
{
	this->songs.at(0)->playMusic();
}

void Game::playEndMusic()
{
	if (this->musicSwitchState == 1)
	{
		this->musicSwitchState -= 1;
		this->stopMainMusic();
		this->songs.at(this->songs.size() - 1)->playMusic();
	}
}

void Game::stopMainMusic()
{
	this->songs.at(0)->stopMusic();
}


void Game::stopEndMusic()
{
	this->songs.at(this->songs.size() - 1)->stopMusic();
}

#pragma endregion

void Game::update()
{
	this->updateDeltaTime();
	this->updatePollEvents();
	this->updateGui();
	this->updatePlayer();
	this->spawnEnemies();
	this->updateCollision();
	this->updateCombat();
	this->updateEnemies();
	this->updateBullets();
	this->updatePickups();
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

	this->renderWorld();

	this->map->render(this->window);

	this->renderPlayer();

	for (size_t i = 0; i<bullets.size(); i++)
	{
		bullets[i]->render(this->window);
	}

	//Rendering enemies
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(this->window);
	}

	for (size_t i = 0; i < pickups.size(); i++)
	{
		pickups[i]->render(this->window);
	}

	this->gui->render(this->window);

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}



void Game::savePoints()
{
	if (this->musicSwitchState == 1)
	{
		this->textManager = new TextFileManager();
		this->textManager->saveToFile(this->points, this->scoreFilePath);
	}
}

void Game::over()
{
	this->savePoints();
	this->updatePollEvents();
	this->gui->updateGameOver();
	this->gui->renderGameOver(this->window);
	this->playEndMusic();
	this->window.display();
}








