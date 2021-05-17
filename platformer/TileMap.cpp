#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"

void TileMap::setDimensions(sf::Vector2u windowSize_)
{
	this->gridSize = 48.f;		//Set the size of one tile
	this->gridSizeI = static_cast<int>(this->gridSize);
	this->dimension.x = windowSize_.x / static_cast<unsigned>(gridSize);
	this->dimension.y = windowSize_.y / static_cast<unsigned>(gridSize);

	this->map.resize(dimension.x, std::vector<Tile*>());
	for (int x = 0; x < dimension.x; x++)
	{
		this->map[x].resize(dimension.y, NULL);
	}
}

TileMap::TileMap(sf::Texture* textureSheet_, sf::Vector2u windowSize_, std::string mapFilePath_)
{
	this->setDimensions(windowSize_);
	this->textureSheet = textureSheet_;

	//Collision area
	fromX = 0;
	toX = 0;
	fromY = 0;
	toY = 0;

	//this->update();
	this->loadFromFile(mapFilePath_);
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->dimension.x; x++)
	{
		for (size_t y = 0; y < this->dimension.y; x++)
		{
			delete this->map[x][y];
		}
	}
}

void TileMap::addTile(const float x, const float y)
{
}


void TileMap::loadFromFile(const std::string file_name)
{
	std::string line;			//File should contain windowSize.x/gridSize.x rows of values, comma separated
	std::ifstream in_file;		//File should contain windowSize.y/gridSize.y columns of values, comma separated
	in_file.open(file_name);	//Current config: rows = 30, columns = 19

	if (in_file.is_open())
	{
		this->map.resize(dimension.x, std::vector<Tile*>());
		for (int x = 0; x < dimension.x; x++)
		{
			this->map[x].resize(dimension.y, NULL);
		}

			std::string loadedCell;
			for (int y = 0; y < dimension.y; y++)
			{
				std::getline(in_file, line);
				std::stringstream str(line);
				for (int x = 0; x < dimension.x; x++)
				{
					std::getline(str, loadedCell, ' ');			//WATCH FOR SPACES AT THE END OF LINE!!!
					if (std::stoi(loadedCell) == 0)
					{
						this->map[x][y] = NULL;
					}
					else if (std::stoi(loadedCell) == 1)
					{
						this->map[x][y] = new Tile(x * this->gridSize, y * gridSize, gridSize, this->textureSheet, true);
					}
					else
					{
						std::cout << "ERRER::TILEMAP::INVALID VALUE IN FILE:" << file_name 
						<< "ROW " << x << "COLUMN " << y << ", LOADED NULL INSTEAD" << std::endl;
						this->map[x][y] = NULL;
					}
				}
			}
		in_file.close();
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << std::endl;
		in_file.close();
	}
}

void TileMap::updateCollision(Player* player)
{
	//Initializing collision area
	this->fromX = player->getGridPosition(gridSizeI).x -2;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->dimension.x)
		this->fromX = this->dimension.x;

	this->toX = player->getGridPosition(gridSizeI).x + 2;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->dimension.x)
		this->toX = this->dimension.x;

	this->fromY = player->getGridPosition(gridSizeI).y - 3;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->dimension.y)
		this->fromY = dimension.y;

	this->toY = player->getGridPosition(gridSizeI).y +3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->dimension.y)
		this->toY = dimension.y;


	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			if (map[x][y] != NULL)
			{
				enum borderLocation { None = 0, Left = 1, Right = 2 }; //Indicates if current tile borders on the left edge or right edge
				sf::FloatRect nextPos;
				sf::FloatRect playerBounds = player->getGlobalBounds();
				sf::FloatRect tileBounds = map[x][y]->getGlobalBounds();
				sf::Vector2f velocity = player->getVelocity();

				nextPos = playerBounds;
				nextPos.left += velocity.x;
				nextPos.top += velocity.y;

				//Bordering

				if (tileBounds.intersects(nextPos))
				{
					//Bottom collision
					if (playerBounds.top < tileBounds.top
						&& playerBounds.top + playerBounds.height < tileBounds.top + tileBounds.height
						&& playerBounds.left < tileBounds.left + tileBounds.width
						&& playerBounds.left + playerBounds.width > tileBounds.left)
					{
						player->resetVelocityY();
						player->setPosition(playerBounds.left, tileBounds.top - playerBounds.height);
						player->resetJumping();
					}

					//Top collision
					else if (playerBounds.top > tileBounds.top
						&& playerBounds.top + playerBounds.height > tileBounds.top + tileBounds.height
						&& playerBounds.left < tileBounds.left + tileBounds.width
						&& playerBounds.left + playerBounds.width > tileBounds.left)
					{
						player->resetVelocityY();
						player->setPosition(playerBounds.left, tileBounds.top + playerBounds.height);
					}


					////Right collision
					//if (playerBounds.left < tileBounds.left
					//	&& playerBounds.left + playerBounds.width < tileBounds.left + tileBounds.width
					//	&& playerBounds.top < tileBounds.top + tileBounds.height
					//	&& playerBounds.top + playerBounds.height > tileBounds.top)
					//{
					//	player->resetVelocityX();
					//	player->setPosition(tileBounds.left - playerBounds.width, playerBounds.top);
					//}

					////Left collision
					//else if (playerBounds.left > tileBounds.left
					//	&& playerBounds.left + playerBounds.width > tileBounds.left + tileBounds.width
					//	&& playerBounds.top < tileBounds.top + tileBounds.height
					//	&& playerBounds.top + playerBounds.height > tileBounds.top)
					//{
					//	player->resetVelocityX();
					//	player->setPosition(tileBounds.left + tileBounds.width, playerBounds.top);
					//}
				}
			}
		}
	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (int x = 0; x < this->dimension.x; x++)
	{
		for (int y = 0; y < this->dimension.y; y++)
		{
			if(this->map[x][y] != NULL)
			this->map[x][y]->render(target);
		}
	}
}
