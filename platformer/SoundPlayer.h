#pragma once
class SoundPlayer
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;

	void initVariables(std::string filePath_, int volume_);

public:
	SoundPlayer(std::string filePath_, int volume_);
	~SoundPlayer();

	//functions
	
	void update();
	void playSound();
};

