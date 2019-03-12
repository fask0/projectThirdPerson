#ifndef TOASTERTOWER_HPP
#define TOASTERTOWER_HPP

#include <string>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/SoundEffects.hpp"

#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/core/ToasterProjectile.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class ToasterTower : public Tower
{
	public:
	ToasterTower();
	virtual ~ToasterTower();

	void update(float pStep) override;

	static Mesh* Mesh;
	static LitTextureMaterial* Material;
	static std::vector<SoundEffect*> SFX;

	void AddTowerBehaviour() override;

	ToasterProjectile* primedProjectile = nullptr;
	void PlayAttackSound();

	private:
	ToasterTower(const ToasterTower&);
	ToasterTower& operator= (const ToasterTower&);
};

#endif // CAMERA_HPP
