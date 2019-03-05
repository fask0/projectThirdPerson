#pragma once

#include <iostream>
#include <vector>

#include "mge/core/Enemy.hpp"
#include "mge/core/Mesh.hpp"

#include "mge/materials/AbstractMaterial.hpp"

class Rat : public Enemy
{
public:
	static Mesh* Mesh;
	static AbstractMaterial* Material;

	Rat(std::string pName = "Rat",
		glm::vec3 pPosition = glm::vec3(0, 0, 0),
		Waypoint::Lane pLane = Waypoint::A,
		std::string pTag = "ratEnemy");
	~Rat();

	virtual void update(float pStep);
};