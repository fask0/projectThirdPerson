#include "SoundEffects.hpp"
#include "mge/core/GameController.hpp"

SoundEffect::SoundEffect(const std::string & pFilePath, SoundType pType) : _soundType(pType)
{
	SetSoundEffect(pFilePath);
	SetVolume(100);
}

SoundEffect::~SoundEffect()
{
}

void SoundEffect::SetSoundEffect(const std::string & pFilePath)
{
	switch (_soundType)
	{
		case SoundEffect::Music:
		if (_music.openFromFile(pFilePath))
			_music.setLoop(true);
		else
			std::cout << "Music: " + pFilePath + " was not found..." << std::endl;
		break;

		case SoundEffect::SFX:
		if (_buffer.loadFromFile(pFilePath))
			_sound.setBuffer(_buffer);
		else
			std::cout << "Sound: " + pFilePath + " was not found..." << std::endl;
		break;
	}
}

void SoundEffect::SetVolume(float pVolume)
{
	switch (_soundType)
	{
		case SoundEffect::Music:
		if (pVolume > GameController::MaxMusicVolume)
			_music.setVolume(GameController::MaxMusicVolume);
		else
			_music.setVolume(pVolume);

		break;

		case SoundEffect::SFX:
		if (pVolume > GameController::MaxSFXVolume)
			_sound.setVolume(GameController::MaxSFXVolume);
		else
			_sound.setVolume(pVolume);
		break;
	}
}

float SoundEffect::GetVolume()
{
	switch (_soundType)
	{
		case SoundEffect::Music:
		return _music.getVolume();
		break;

		case SoundEffect::SFX:
		return _sound.getVolume();
		break;
	}
}

void SoundEffect::Play()
{
	switch (_soundType)
	{
		case SoundEffect::Music:
		_music.play();
		break;

		case SoundEffect::SFX:
		_sound.play();
		break;
	}
}

void SoundEffect::Pause()
{
	switch (_soundType)
	{
		case SoundEffect::Music:
		_music.pause();
		break;

		case SoundEffect::SFX:
		_sound.pause();
		break;
	}
}
