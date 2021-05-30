#pragma once
class SubMenu
{
private:

protected:
	sf::RenderWindow window;
	sf::Event event;
	sf::Font font;
	sf::Text text;
	bool clickedEscape;

	void initWindow(std::string title_);
	void loadFont();
	virtual void initVariables();
public:
	SubMenu();
	~SubMenu();

	void endState();
	bool wasEscapePressed();

	void updatePollEvents();
	virtual void update();
	virtual void render();

	const sf::RenderWindow& getWindow() const;
};

