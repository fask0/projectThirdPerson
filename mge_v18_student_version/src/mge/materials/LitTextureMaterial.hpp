#pragma once 

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
//#include "mge/config.hpp"

class ShaderProgram;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class LitTextureMaterial : public AbstractMaterial
{
	public:
	LitTextureMaterial(Texture* pDiffuseTexture);
	virtual ~LitTextureMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	//in rgb values
	void setDiffuseTexture(Texture* pDiffuseTexture);

	bool _settingDiffuseTextureManually = false;
	unsigned int _depthMap;
	float _nearPlane = 0.1f;
	float _farPlane = 1000.0f;

	private:
	//all the static properties are shared between instances of LitMaterial
	//note that they are all PRIVATE, we do not expose this static info to the outside world
	ShaderProgram* _shader;
	void initShader();

	//this one is unique per instance of material
	Texture* _diffuseTexture;
};

class DebugTextureMaterial : public LitTextureMaterial
{
	private:
	ShaderProgram* m_shader;

	public:
	DebugTextureMaterial(Texture* pDiffuseTexture);
	virtual ~DebugTextureMaterial() { delete m_shader; }

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
};
