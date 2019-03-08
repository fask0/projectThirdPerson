#ifndef TOASTERPROJECTILE_HPP
#define TOASTERPROJECTILE_HPP

#include <string>
#include "mge/core/GameObject.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include <time.h>

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class ToasterProjectile : public GameObject
{
	public:
	ToasterProjectile(glm::mat4 pTransform);

	virtual ~ToasterProjectile();

	void update(float pStep) override;

	void OnCollisionEnter(GameObject* pOther) override;
	bool SkipCollisionCheck() override;

	static Mesh* Mesh;
	static LitTextureMaterial* Material;

	void Shoot();

	protected:
	ToasterProjectile(const ToasterProjectile&);
	ToasterProjectile& operator= (const ToasterProjectile&);
	clock_t _spawnTime;
	glm::vec3 _spawnPos;
	bool _isShooting;
	bool _onToaster = true;
};

#endif // CAMERA_HPP
