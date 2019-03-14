#pragma once

#include "SFML/Audio.hpp"
#include <iostream>

class SoundEffect
{
	public:
	enum SoundType
	{
		Music,
		SFX
	};

	SoundEffect(const std::string & pFilePath, SoundType pType);
	~SoundEffect();

	void SetSoundEffect(const std::string & pFilePath);

	sf::Sound& GetSound() { return _sound; }
	sf::Music& GetMusic() { return _music; }

	void SetVolume(float pVolume);
	float GetVolume();

	void Play();
	void Pause();

	SoundType GetType() { return _soundType; }

	private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	sf::Music _music;

	SoundType _soundType;
};