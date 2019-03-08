#ifndef ICEPROJECTILE_HPP
#define ICEPROJECTILE_HPP

#include <string>
#include "mge/core/GameObject.hpp"
#include "mge/core/Texture.hpp"
#include <time.h>

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class IceProjectile : public GameObject
{
	public:
	IceProjectile(glm::mat4 pTransform);

	virtual ~IceProjectile();
	void update(float pStep) override;

	void OnCollisionEnter(GameObject* pOther) override;
	bool SkipCollisionCheck() override;

	static Mesh* Mesh;
	static Texture* Texture;

	protected:
	IceProjectile(const IceProjectile&);
	IceProjectile& operator= (const IceProjectile&);
	clock_t _spawnTime;
	glm::vec3 _spawnPos;
	private:
	bool _hasHitEnemy = false;
};

#endif // CAMERA_HPP
