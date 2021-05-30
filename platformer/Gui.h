#pragma once
class Gui
{
private:
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;

	sf::RectangleShape gameOverShape;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Variables
	sf::Vector2f pointTextPos;
	sf::Vector2f gameOverTextPos;
	int characterSize;
	int counter;
	int maxCounter;

	sf::Vector2f hpBarSize;

	//Init functions
	void initVariables();
	void loadFont();
	void initPointText();
	void initGameOverText();
	void initGameOverRectangle();
	void initPlayerHpBar();
	void initElements();

public:
	Gui();
	~Gui();

	//Update
	void updatePointText(int points_);
	void updatePlayerHpBar(int hp_, int hpMax_);
	void update(int points_, int hp_, int hpMax_);

	void animateGameOverRectangle(int counter_);
	void animateGameOverText(int counter_);
	void updateGameOver();

	//Render
	void render(sf::RenderTarget& target);
	void renderGameOver(sf::RenderTarget& target);
};

