#pragma once
class Tile
{
private:
	sf::Sprite shape;
	sf::RectangleShape rect;
	bool isPhysical;
	float tileSize = 16.f;


public:
	Tile(float x, float y, float gridSizeF, sf::Texture* texture_, bool isPhysical_);
	Tile();
	~Tile();

	//Functions
	sf::FloatRect getGlobalBounds();
	bool getPhysical();

	void update();
	void render(sf::RenderTarget& target);
};

