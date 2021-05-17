#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, sf::Texture* texture_, bool isPhysical_)
{
	this->isPhysical = isPhysical_;
	this->shape.setTexture(*texture_);
	this->shape.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->shape.setScale(gridSizeF / tileSize, gridSizeF / tileSize);
	this->shape.setPosition(x, y);
}


Tile::Tile()
{
}

Tile::~Tile()
{
}


sf::FloatRect Tile::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
