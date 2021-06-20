#pragma once
class MenuBox
{
private:
	sf::Vector2f size;
	sf::Texture imageTexture;
	sf::Sprite image;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	bool imageExists;
public:
	MenuBox(float height_, float width_, float posX_, float posY_, std::string text_, sf::Font font_, int fontSize_);
	MenuBox(float height_, float width_, float posX_, float posY_, std::string imagePath_);
	~MenuBox();

	//Accessors
	const sf::FloatRect getPanelBounds() const;

	//Functions
	void changeTextColor(sf::Color color_);
	void changeBoxColor(sf::Color color_);
	void update();
	void render(sf::RenderTarget& target);
};

