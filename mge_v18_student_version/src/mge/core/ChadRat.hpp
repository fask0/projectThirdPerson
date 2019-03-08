#pragma once

#include <iostream>
#include <vector>

#include "mge/core/Enemy.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"

#include "mge/materials/AbstractMaterial.hpp"

class ChadRat : public Enemy
{
	public:
	static std::vector<Mesh*> Animation;
	static Texture* Texture;

	ChadRat(std::string pName = "Rat",
			glm::vec3 pPosition = glm::vec3(0, 0, 0),
			Waypoint::Lane pLane = Waypoint::A,
			std::string pTag = "enemy");
	~ChadRat();

	virtual void update(float pStep);
};