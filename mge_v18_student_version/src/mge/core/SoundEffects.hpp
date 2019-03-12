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

	void SetVolume(float pVolume) { _sound.setVolume(pVolume); }
	float GetVolume() { return _sound.getVolume(); }

	void PlaySoundEffect() { _sound.play(); }
	void SetPitch(float pPitch) { _sound.setPitch(pPitch); }

	SoundType GetType() { return _soundType; }

	private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;

	SoundType _soundType;
};