#ifndef HONEYTOWER_HPP
#define HONEYTOWER_HPP

#include <iostream>
#include <vector>
#include <string>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class HoneyTower : public Tower
{
	public:
	HoneyTower();
	virtual ~HoneyTower();

	void update(float pStep) override;

	static Mesh* MainMesh;
	static Mesh* MouseMesh;
	static AbstractMaterial* MainMaterial;
	static AbstractMaterial* MouseMaterial;

	GameObject* getMouse() { return _mouse; }
	void AddTowerBehaviour() override;

	private:
	HoneyTower(const HoneyTower&);
	HoneyTower& operator= (const HoneyTower&);
	GameObject* _mouse = nullptr;
	bool _isMouseInit = false;
};

#endif // CAMERA_HPP
