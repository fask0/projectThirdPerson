#ifndef HONEYPROJECTILE_HPP
#define HONEYPROJECTILE_HPP

#include <string>
#include "mge/core/GameObject.hpp"
#include <time.h>
#include "mge/core/Enemy.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class HoneyProjectile : public GameObject
{
	public:
	HoneyProjectile(glm::mat4 pTransform, float pDiff);

	virtual ~HoneyProjectile();

	void update(float pStep) override;

	void OnCollisionEnter(GameObject* pOther) override;
	void OnCollisionExit(GameObject* pOther) override;
	bool SkipCollisionCheck() override;

	static Mesh* Mesh;
	static LitTextureMaterial* Material;

	protected:
	HoneyProjectile(const HoneyProjectile&);
	HoneyProjectile& operator= (const HoneyProjectile&);
	clock_t _spawnTime;
	glm::vec3 _spawnPos;
	std::vector<Enemy*> enemiesCollidingWith;
};

#endif // CAMERA_HPP
