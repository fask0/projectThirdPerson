#ifndef SHOCKTOWER_HPP
#define SHOCKTOWER_HPP

#include <string>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"

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

	static Mesh* Mesh;
	static AbstractMaterial* Material;

private:
	ShockTower(const ShockTower&);
	ShockTower& operator= (const ShockTower&);
};

#endif // CAMERA_HPP
