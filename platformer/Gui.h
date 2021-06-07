#pragma once
class Gui
{
private:
	sf::Text pointText;
	sf::Text gameOverText;

	sf::RectangleShape gameOverShape;

	//Variables
	sf::Vector2f pointTextPos;
	sf::Vector2f gameOverTextPos;
	int counter;
	int maxCounter;

	//Init functions
	void initPointText();
	void initGameOverText();
	void initGameOverRectangle();

protected:
	sf::Font font;
	sf::Text hpText;

	sf::RectangleShape HpBar;
	sf::RectangleShape HpBarBack;

	//Variables
	int characterSize;
	sf::Vector2f hpTextPos;
	sf::Vector2f hpBarSize;

	//Init functions
	virtual void initVariables();
	void loadFont();
	void initHpText();
	void initHpBar();
	virtual void initElements();


public:
	Gui();
	~Gui();

	//Update
	void updatePointText(int points_);
	virtual void updateHpText(int hp_, int hpMax_);
	virtual void updateHpBar(int hp_, int hpMax_);
	virtual void update(int points_, int hp_, int hpMax_);

	void animateGameOverRectangle(int counter_);
	void animateGameOverText(int counter_);
	void updateGameOver();

	//Render
	virtual void render(sf::RenderTarget& target);
	void renderGameOver(sf::RenderTarget& target);
};

