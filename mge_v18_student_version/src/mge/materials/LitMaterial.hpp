#pragma once
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Light.hpp"
#include "GL/glew.h"

class ShaderProgram;

class LitMaterial : public AbstractMaterial
{
public:
	LitMaterial(Light *light, glm::vec3 pColor = glm::vec3(1, 0, 0));
	virtual ~LitMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	//in rgb values
	void setDiffuseColor(glm::vec3 pDiffuseColor);
	void AddLight(Light *light);

private:
	//all the static properties are shared between instances of LitMaterial
	//note that they are all PRIVATE, we do not expose this static info to the outside world
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	std::vector<Light*> _lights;

	glm::vec3 _diffuseColor;
	Light *_light;
};
