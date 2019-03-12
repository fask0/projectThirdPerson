#include "SoundEffects.hpp"

SoundEffect::SoundEffect(const std::string & pFilePath, SoundType pType)
{
	SetSoundEffect(pFilePath);
}

SoundEffect::~SoundEffect()
{
}

void SoundEffect::SetSoundEffect(const std::string & pFilePath)
{
	if (_buffer.loadFromFile(pFilePath))
		_sound.setBuffer(_buffer);
	else
		std::cout << "Sound: " + pFilePath + " was not found..." << std::endl;
}
