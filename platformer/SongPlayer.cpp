#include "stdafx.h"
#include "SongPlayer.h"

void SongPlayer::initVariables(std::string filePath_, int volume_, bool loop_)
{
	if (!this->music.openFromFile(filePath_))
		std::cout << "Couldn't load file " << filePath_ << std::endl;
	this->music.setVolume(volume_);
	this->music.setLoop(loop_);
}

SongPlayer::SongPlayer(std::string filePath_, int volume_, bool loop_)
{
	this->initVariables(filePath_, volume_, loop_);
}

SongPlayer::~SongPlayer()
{
	this->stopMusic();
}

void SongPlayer::stopMusic()
{
	this->music.stop();
}

void SongPlayer::update()
{
}

void SongPlayer::playMusic()
{
	this->music.play();
}
