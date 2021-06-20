#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy_Fire.h"
#include "Pickup.h"
#include "Tile.h"
#include "TileMap.h"
#include "Gui.h"
#include "SongPlayer.h"
#include "SoundPlayer.h"
#include "TextFileManager.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;

	Gui* gui;
	Player* player;
	TextFileManager* textManager;


	//Variables
	sf::Vector2f randomCorner;
	sf::Clock clock;
	float deltaTime;
	float accTimer;
	float spawnTimer, spawnTimerMax;
	sf::Clock shootingTimer;

	//Resources
	std::string mapFilePath, scoreFilePath;
	sf::Sprite backgroundTexture;
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<Enemy_Fire*> enemies; //TODO Generalize vector to all types of enemies
	std::vector<Pickup*> pickups;
	TileMap* map;

	//Gui/gameplay elements
	int points;

	//Audio elements
	int musicVol, soundVol;
	std::map<std::string, std::string> audioPath;
	std::vector<SongPlayer*> songs;
	std::vector<SoundPlayer*> sounds;
	int musicSwitchState;

	void initVariables();
	void initWindow();
	void initBackground();
	void initGui();
	void initTextures();
	void initMusic();
	void initSounds();
	void initPlayer();
	void initTileMap();
public:

	Game(int musicVol_, int soundVol_, std::string selectedMap_);
	~Game();

	//Accessors
	sf::Texture* getTexture(std::string texture_);
	const int getPlayerHp() const;

	//Spawn
	void spawnEnemies();
	void spawnPickup(const sf::Vector2f& pos_);

	//Updates
	void updateDeltaTime();
	void updatePollEvents();
	void updatePlayer();
	void updateGui();
	void updateCollision();
	void updateCombat();
	void updateEnemies();
	void updateBullets();
	void updatePickups();
	void update();

	//Music
	void playMainMusic();
	void stopMainMusic();
	void playEndMusic();
	void stopEndMusic();


	//Render
	void renderPlayer();
	void renderWorld();
	void render();
	const sf::RenderWindow& getWindow() const;

	void savePoints();
	void over();
};

