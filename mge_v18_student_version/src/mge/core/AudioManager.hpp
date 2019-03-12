#pragma once

#include <iostream>
#include <vector>

#include "SFML/Audio.hpp"

#include "mge/core/SoundEffects.hpp"
#include "mge/core/GameObject.hpp"

#include "glm.hpp"

class AudioManager : public GameObject
{
	public:
	AudioManager(std::string pName = "AudioManager",
				 glm::vec3 pPosition = glm::vec3(0, 0, 0));
	~AudioManager();
	void update(float pStep) override;
};