#pragma once
#include "Tile.h"
#include <vector>

class TileMap
{
private:
	sf::Texture* textureSheet;
	float gridSize;
	int gridSizeI;
	sf::Vector2i dimension; //how many tiles in a screen (one tile = 16x16 pixels)
	std::vector<std::vector<Tile*>> map;

	//Collision area
	int fromX;
	int toX;
	int fromY;
	int toY;

	void setDimensions(sf::Vector2u windowSize_);

public:
	TileMap(sf::Texture* textureSheet, sf::Vector2u windowSize, std::string mapFilePath_);
	~TileMap();

	void addTile(const float x, const float y); 

	void loadFromFile(const std::string file_name);
	void updateCollision(Player* player);
	void update();
	void render(sf::RenderTarget& target);
};

