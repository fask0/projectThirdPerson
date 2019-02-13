#ifndef TEXTUREGRIDMATERIAL_HPP
#define TEXTUREGRIDMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TextureGridMaterial : public AbstractMaterial
{
	public:
	TextureGridMaterial(Texture* pDiffuseTexture);
	virtual ~TextureGridMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseTexture(Texture* pDiffuseTexture);
	void setHighlightArea(glm::vec3 mousePos);
	void toggleGrid();
	void setGridSize(float size);
	float getGridSize();
	void setLineThiccness(float thiccness);
	float getLineThiccness();

	protected:
	private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;

	static GLint _uDiffuseTexture;
	static GLint _uMousePos;
	static GLint _uGridVisible;
	static GLint _uLineThiccness;
	static GLint _uGridSize;

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	Texture* _diffuseTexture;

	TextureGridMaterial(const TextureGridMaterial&);
	TextureGridMaterial& operator=(const TextureGridMaterial&);

	bool _gridShowing;
	float _gridSize = 5;
	float _lineThiccness = 0.3f;
	glm::vec3 _mousePos;
};

#endif // TEXTUREMATERIAL_HPP
