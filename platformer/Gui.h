#pragma once
class Gui
{
private:
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Variables
	sf::Vector2f pointTextPos;
	int characterSize;

	sf::Vector2f hpBarSize;

	//Init functions
	void initVariables();
	void loadFont();
	void initPointText();
	void initGameOverText();
	void initPlayerHpBar();
	void initElements();

public:
	Gui();
	~Gui();

	//Update
	void updatePointText(int points_);
	void updatePlayerHpBar(int hp_, int hpMax_);
	void update(int points_, int hp_, int hpMax_);

	//Render
	void render(sf::RenderTarget& target);
};

