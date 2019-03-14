#pragma once

#include <iostream>
#include <vector>

#include "mge/core/Level.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/Mesh.hpp"

#include "glm.hpp"

class LevelTwo : public Level
{
	public:
	LevelTwo(std::string pName = "LevelTwo",
			 glm::vec3 pPosition = glm::vec3(0, 0, 0),
			 int pLayers = 0);
	~LevelTwo();
	void update(float pStep) override;

	void Init() override;
};
