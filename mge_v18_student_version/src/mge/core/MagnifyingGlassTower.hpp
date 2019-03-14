#ifndef MAGNIFYINGGLASSTOWER_HPP
#define MAGNIFYINGGLASSTOWER_HPP

#include <string>
#include <vector>
#include <time.h>

#include "mge/core/Tower.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/SoundEffects.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

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
	static std::vector<SoundEffect*> SFX;

	void AddTowerBehaviour() override;

	private:
	MagnifyingGlassTower(const MagnifyingGlassTower&);
	MagnifyingGlassTower& operator= (const MagnifyingGlassTower&);
};

class MagnifyingGlassHitBox : public GameObject
{
	public:
	static std::vector < Mesh*> Animations;
	static LitTextureMaterial*  Material;

	MagnifyingGlassHitBox();
	~MagnifyingGlassHitBox();

	void update(float pStep) override;

	void OnCollisionEnter(GameObject* pOther) override;
	void OnCollisionExit(GameObject * pOther) override;
	bool SkipCollisionCheck() override;

	private:
	std::vector<GameObject*> _objectsInRange;
	time_t _timer = 0;
	int _currentFrame = 0;
	bool _goBack = false;
};

#endif // CAMERA_HPP
