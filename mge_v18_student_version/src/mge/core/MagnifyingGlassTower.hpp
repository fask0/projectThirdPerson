#ifndef MAGNIFYINGGLASSTOWER_HPP
#define MAGNIFYINGGLASSTOWER_HPP

#include <string>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"

#include "mge/materials/AbstractMaterial.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class MagnifyingGlassTower : public Tower
{
public:
	MagnifyingGlassTower();
	virtual ~MagnifyingGlassTower();

	void update(float pStep) override;

	static Mesh* Mesh;
	static AbstractMaterial* Material;

	void AddTowerBehaviour() override;

	void OnCollisionEnter(GameObject* pOther) override;

private:
	MagnifyingGlassTower(const MagnifyingGlassTower&);
	MagnifyingGlassTower& operator= (const MagnifyingGlassTower&);
};

#endif // CAMERA_HPP
