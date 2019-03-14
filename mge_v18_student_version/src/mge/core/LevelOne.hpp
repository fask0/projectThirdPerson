#pragma once

#include <iostream>
#include <vector>

#include "mge/core/Level.hpp"
#include "mge/core/EnemySpawner.hpp"
#include "mge/core/Mesh.hpp"

#include "glm.hpp"

class LevelOne : public Level
{
	public:
	LevelOne(std::string pName = "LevelOne",
			 glm::vec3 pPosition = glm::vec3(0, 0, 0),
			 int pLayers = 0);
	~LevelOne();
	void update(float pStep) override;

	void Init() override;
};
