#ifndef LITTEXTUREMATERIAL_HPP
#define LITTEXTUREMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"

class ShaderProgram;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class LitTextureMaterial : public AbstractMaterial
{
public:
	LitTextureMaterial(Light *light, Texture* pDiffuseTexture);
	virtual ~LitTextureMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	//in rgb values
	void setDiffuseTexture(Texture* pDiffuseTexture);
	void AddLight(Light *light);

private:
	//all the static properties are shared between instances of LitMaterial
	//note that they are all PRIVATE, we do not expose this static info to the outside world
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	std::vector<Light*> _lights;

	//this one is unique per instance of color material
	Texture* _diffuseTexture;
	Light *_light;
};

#endif // LitMaterial_HPP
