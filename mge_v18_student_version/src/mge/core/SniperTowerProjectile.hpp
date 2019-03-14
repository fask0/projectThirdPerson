#pragma once
#include <iostream>

#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"

#include "mge/materials/LitTextureMaterial.hpp"

#include "glm.hpp"

class SniperTowerProjectile : public GameObject
{
	public:
	static Mesh* Mesh;
	static LitTextureMaterial* Material;

	SniperTowerProjectile(glm::vec3 pPosition, GameObject* pTarget);
	~SniperTowerProjectile();
	void update(float pStep) override;

	private:
	GameObject* _targetPos;
	int _speed = 0;
	glm::vec3 _dist;
	glm::vec3 _dir;
};