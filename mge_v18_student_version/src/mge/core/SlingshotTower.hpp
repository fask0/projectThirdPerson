#ifndef SLINGSHOTTOWER_HPP
#define SLINGSHOTTOWER_HPP

#include <string>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"

#include "mge/materials/AbstractMaterial.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class SlingshotTower : public Tower
{
public:
	SlingshotTower();
	virtual ~SlingshotTower();

	void update(float pStep) override;

	static Mesh* Mesh;
	static AbstractMaterial* Material;

private:
	SlingshotTower(const SlingshotTower&);
	SlingshotTower& operator= (const SlingshotTower&);
};

#endif // CAMERA_HPP
