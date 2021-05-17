#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy_Fire.h"
#include "Tile.h"
#include "TileMap.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;

	Player* player;

	//Resources
	std::string mapFilePath;
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<Enemy_Fire*> enemies; //TODO Generalize vector to all types of enemies
	TileMap* map;

	void initWindow();
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
	void updatePollEvents();
	void updatePlayer();
	void updateCollision();
	void updateEnemies();
	void updateBullets();
	void update();

	//Render
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};

