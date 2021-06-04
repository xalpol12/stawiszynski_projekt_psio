#pragma once
#include "Tile.h"
#include "Pickup.h"
#include "Player.h"
#include "Bullet.h"

class TileMap
{
private:
	sf::Texture* textureSheet;
	float gridSize;
	int gridSizeI;
	sf::Vector2i dimension; //how many tiles in a screen (one tile = 16x16 pixels)
	std::vector<std::vector<Tile*>> map;

	//Collision area
	int fromX, toX, fromY, toY;

	void setDimensions(sf::Vector2u windowSize_);

public:
	TileMap(sf::Texture* textureSheet, sf::Vector2u windowSize, std::string mapFilePath_);
	~TileMap();

	void addTile(const float x, const float y); 

	void loadFromFile(const std::string file_name);
	void updatePlayerCollision(Player* player);
	bool updateBulletCollision(Bullet* bullet);
	void updatePickupCollision(Pickup* pickup);

	void update();
	void render(sf::RenderTarget& target);
};

