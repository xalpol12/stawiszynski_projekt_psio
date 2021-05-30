#pragma once
class SongPlayer
{
private:
	sf::Music music;

	void initVariables(std::string filePath_, int volume_, bool loop_);
public:
	SongPlayer(std::string filePath_ ,int volume_, bool loop_);
	~SongPlayer();

	//functions
	void stopMusic();

	void update();
	void playMusic();
};

