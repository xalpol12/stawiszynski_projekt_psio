#pragma once
#include "Gui.h"

class EnemyUI : public Gui
{
private:
	sf::FloatRect enemyDimensions;
	sf::Text damageText;
	float offsetX, offsetY;
	sf::Uint8 transparency;
	
	void initDamageText();
	void initVariables();
	void initElements();

public:
	EnemyUI(const sf::FloatRect& size_, const float& offsetX_, const float& offsetY_);
	~EnemyUI();

	//Functions
	void damageAnimation(int damage_, sf::Vector2f pos_);
	
	//Updates
	void updateHpText(const int& hp_, const int& hpMax_, const sf::Vector2f& pos_);
	void updateHpBar(const int& hp_, const int& hpMax_, const sf::Vector2f& pos_);
	void updateDamageText();
	void update(const int& hp_, const int& hpMax_, const sf::Vector2f& pos_);

	void render(sf::RenderTarget& target);
};

