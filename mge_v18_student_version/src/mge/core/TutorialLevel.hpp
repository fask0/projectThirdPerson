#pragma once

#include <iostream>
#include <vector>

#include "mge/core/Level.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/Mesh.hpp"

#include "glm.hpp"

class TutorialLevel : public Level
{
	public:
	TutorialLevel(std::string pName = "TutorialLevel",
				  glm::vec3 pPosition = glm::vec3(0, 0, 0),
				  int pLayers = 0);
	~TutorialLevel();
	void update(float pStep) override;

	void Init() override;
};