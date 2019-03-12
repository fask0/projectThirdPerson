#ifndef SHOCKTOWER_HPP
#define SHOCKTOWER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <time.h>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class ShockTower : public Tower
{
	public:
	ShockTower();
	virtual ~ShockTower();

	void update(float pStep) override;

	static Mesh* MainMesh;
	static std::vector<Mesh*> Animations;
	static AbstractMaterial* AnimationMaterial;

	void AddTowerBehaviour() override;

	private:
	ShockTower(const ShockTower&);
	ShockTower& operator= (const ShockTower&);

	GameObject* _aoeModel = nullptr;
	int _currentFrame = 0;
	time_t _timer = 0;
};

#endif // CAMERA_HPP
