#include "stdafx.h"
#include "SoundPlayer.h"

void SoundPlayer::initVariables(std::string filePath_, int volume_)
{
	if (!buffer.loadFromFile(filePath_))
		std::cout << "Couldn't load file " << filePath_ << std::endl;
	this->sound.setBuffer(this->buffer);
	this->sound.setVolume(volume_);
}

SoundPlayer::SoundPlayer(std::string filePath_, int volume_)
{
	this->initVariables(filePath_, volume_);
}

SoundPlayer::~SoundPlayer()
{
	this->sound.stop();
}

void SoundPlayer::update()
{
}

void SoundPlayer::playSound()
{
	this->sound.play();
}
