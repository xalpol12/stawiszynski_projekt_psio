#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy_Fire.h"
#include "Tile.h"
#include "TileMap.h"
#include "Gui.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;

	Gui* gui;
	Player* player;


	//Variables
	sf::Vector2f randomCorner;
	sf::Clock clock;
	float deltaTime;
	float accTimer;
	float spawnTimer, spawnTimerMax;
	sf::Clock shootingTimer;

	//Resources
	std::string mapFilePath;
	sf::Sprite backgroundTexture;
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<Enemy_Fire*> enemies; //TODO Generalize vector to all types of enemies
	TileMap* map;

	//Gui/gameplay elements
	int points;

	void initVariables();
	void initWindow();
	void initBackground();
	void initGui();
	void initTextures();
	void initPlayer();
	void initTileMap();
public:

	Game();
	~Game();

	//Accessors
	sf::Texture* getTexture(std::string texture_);

	//Spawn
	void spawnEnemies();

	//Updates
	void updateDeltaTime();
	void updatePollEvents();
	void updatePlayer();
	void updateGui();
	void updateCollision();
	void updateCombat();
	void updateEnemies();
	void updateBullets();
	void update();

	//Render
	void renderPlayer();
	void renderWorld();
	void render();
	const sf::RenderWindow& getWindow() const;
};

