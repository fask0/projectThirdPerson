#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class Tower : public GameObject
{
public:
	Tower(
		std::string pName = "Tower",
		glm::vec3 pPosition = glm::vec3(0.0f, 0.0f, 0.0f),
		float pRange = 3.0f,
		AbstractMaterial* pMaterial = new ColorMaterial(glm::vec4(0, 1, 0, 1)));

	virtual ~Tower();

	void update(float pStep) override;
	void Rotate90();

	void ResetMaterial();
	float GetRange();

private:
	Tower(const Tower&);
	Tower& operator= (const Tower&);

	float _rotation;
	float _range;
	AbstractMaterial* _material;
};

#endif // CAMERA_HPP