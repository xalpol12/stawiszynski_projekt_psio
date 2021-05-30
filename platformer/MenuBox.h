#pragma once
class MenuBox
{
private:
	sf::Vector2f size;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

public:
	MenuBox(float height_, float width_, float posX_, float posY_, std::string text_, sf::Font font_, int fontSize_);
	~MenuBox();

	//Accessors
	const sf::FloatRect getPanelBounds() const;

	//Functions
	void changeTextColor(sf::Color color_);

	void update();
	void render(sf::RenderTarget& target);
};

