#pragma once
#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class ColorMaterial : public AbstractMaterial
{
public:
	ColorMaterial(glm::vec4 pColor = glm::vec4(1, 0, 0, 1));
	virtual ~ColorMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	//in rgb values
	void setDiffuseColor(glm::vec4 pDiffuseColor);

private:
	//all the static properties are shared between instances of ColorMaterial
	//note that they are all PRIVATE, we do not expose this static info to the outside world
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//this one is unique per instance of color material
	glm::vec4 _diffuseColor;
};
