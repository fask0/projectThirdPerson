#pragma once

#include <iostream>
#include <vector>
#include <time.h>

#include "mge/core/Enemy.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/SoundEffects.hpp"

#include "mge/materials/LitTextureMaterial.hpp"

class SanicRat : public Enemy
{
	public:
	static std::vector<SoundEffect*> SFX;
	static std::vector<Mesh*> Animation;
	static LitTextureMaterial* Material;
	static Texture* Texture;

	SanicRat(std::string pName = "Rat",
			 glm::vec3 pPosition = glm::vec3(0, 0, 0),
			 Waypoint::Lane pLane = Waypoint::A,
			 std::string pTag = "enemy");
	~SanicRat();

	virtual void update(float pStep);
};