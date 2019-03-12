#include <iostream>
#include <vector>

#include "AudioManager.hpp"

#include "glm.hpp"

AudioManager::AudioManager(std::string pName, glm::vec3 pPosition)
	: GameObject(pName, pPosition)
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::update(float pStep)
{
	GameObject::update(pStep);
}
