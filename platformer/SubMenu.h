#pragma once
class SubMenu
{
private:

protected:
	sf::RenderWindow window;
	sf::Event event;
	sf::Font font;
	sf::Text text;

	void initWindow(std::string title_);
	void loadFont();
	virtual void initVariables();
public:
	SubMenu();
	~SubMenu();

	void endState();

	void updatePollEvents();
	virtual void update();
	virtual void render();

	const sf::RenderWindow& getWindow() const;
};

