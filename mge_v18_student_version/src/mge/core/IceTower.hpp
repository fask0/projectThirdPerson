#ifndef ICETOWER_HPP
#define ICETOWER_HPP

#include <string>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/SoundEffects.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/IceProjectile.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class IceTower : public Tower
{
	public:
	IceTower();
	virtual ~IceTower();

	void update(float pStep) override;

	static Mesh* Mesh;
	static AbstractMaterial* Material;
	static std::vector<SoundEffect*> SFX;

	void AddTowerBehaviour() override;
	void PlayAttackSound();

	IceProjectile* primedProjectile = nullptr;
	private:
	IceTower(const IceTower&);
	IceTower& operator= (const IceTower&);
};

#endif // CAMERA_HPP
