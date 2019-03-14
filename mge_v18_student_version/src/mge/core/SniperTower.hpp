#ifndef SNIPERTOWER_HPP
#define SNIPERTOWER_HPP

#include <string>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/SoundEffects.hpp"

#include "mge/materials/AbstractMaterial.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class SniperTower : public Tower
{
	public:
	SniperTower();
	virtual ~SniperTower();

	void update(float pStep) override;

	static Mesh* MainMesh;
	static Mesh* MouseMesh;
	static AbstractMaterial* MainMaterial;
	static std::vector<SoundEffect*> SFX;

	GameObject* getMouse() { return _mouse; }
	void AddTowerBehaviour() override;

	void PlayAttackSound();

	private:
	SniperTower(const SniperTower&);
	SniperTower& operator= (const SniperTower&);
	GameObject* _mouse = nullptr;
	bool _isMouseInit = false;
};

#endif // CAMERA_HPP
