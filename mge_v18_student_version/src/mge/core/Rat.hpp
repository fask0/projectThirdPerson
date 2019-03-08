#pragma once

#include <iostream>
#include <vector>

#include "mge/core/Enemy.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"

#include "mge/materials/LitTextureMaterial.hpp"

class Rat : public Enemy
{
	public:
	static std::vector<Mesh*> Animation;
	static LitTextureMaterial* Material;
	static Texture* Texture;

	Rat(std::string pName = "Rat",
		glm::vec3 pPosition = glm::vec3(0, 0, 0),
		Waypoint::Lane pLane = Waypoint::A,
		std::string pTag = "enemy");
	~Rat();

	virtual void update(float pStep);
};
