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
	void setGrid(bool showGrid);

	void toggleRangeShowing();
	void setRangeShowing(bool showRange);
	void SetTowerPos(glm::vec3 pTowerPosition);

	void setGridSize(float size);
	float getGridSize();
	void setLineThiccness(float thiccness);
	float getLineThiccness();
	void setRange(float range);
	float getRange();
	glm::vec3 getMousePos();
	glm::vec3 getTowerPos();

protected:
private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;

	static GLint _uDiffuseTexture;

	static GLint _uGridVisible;
	static GLint _uShowRange;

	static GLint _uMousePos;
	static GLint _uTowerPos;
	static GLint _uLineThiccness;
	static GLint _uGridSize;
	static GLint _uRange;

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	Texture* _diffuseTexture;

	TextureGridMaterial(const TextureGridMaterial&);
	TextureGridMaterial& operator=(const TextureGridMaterial&);

	bool _gridShowing;
	bool _showRange;
	float _gridSize = 5;
	float _lineThiccness = 0.1f;
	float _range = 0;
	glm::vec3 _mousePos;
	glm::vec3 _towerPos;
};

#endif // TEXTUREMATERIAL_HPP
