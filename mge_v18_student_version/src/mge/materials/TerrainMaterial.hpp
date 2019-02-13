#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TerrainMaterial : public AbstractMaterial
{
public:
	TerrainMaterial(Texture* pSplatMap, Texture* pDiffuseTexture0, Texture* pDiffuseTexture1, Texture* pDiffuseTexture2, Texture* pDiffuseTexture3, Texture* pHeightMap, float pTerrainHeight);
	virtual ~TerrainMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseTexture(Texture* pDiffuseTexture);
	void TerrainMaterial::setHighlightArea(glm::vec3 pos);

protected:
private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMVPMatrix;
	static GLint _uHeightMap;
	static GLint _uTerrainHeight;

	static GLint _uSplatMap;
	static GLint _uDiffuseTexture0;
	static GLint _uDiffuseTexture1;
	static GLint _uDiffuseTexture2;
	static GLint _uDiffuseTexture3;

	static GLint _uTime;

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	Texture* _splatMap;
	Texture* _diffuseTexture0;
	Texture* _diffuseTexture1;
	Texture* _diffuseTexture2;
	Texture* _diffuseTexture3;
	Texture* _heightMap;
	float _terrainHeight;

	TerrainMaterial(const TerrainMaterial&);
	TerrainMaterial& operator=(const TerrainMaterial&);

};

#endif // TerrainMaterial_HPP
