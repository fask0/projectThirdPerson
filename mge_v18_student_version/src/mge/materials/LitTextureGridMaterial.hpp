#ifndef LITTEXTUREGRIDMATERIAL_HPP
#define LITTEXTUREGRIDMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"

class ShaderProgram;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class LitTextureGridMaterial : public AbstractMaterial
{
public:
	LitTextureGridMaterial(Light *light, Texture* pDiffuseTexture);
	virtual ~LitTextureGridMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	//in rgb values
	void setDiffuseTexture(Texture* pDiffuseTexture);
	void AddLight(Light *light);

	//Grid stuff
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

private:
	//all the static properties are shared between instances of LitMaterial
	//note that they are all PRIVATE, we do not expose this static info to the outside world
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	std::vector<Light*> _lights;

	//this one is unique per instance of color material
	Texture* _diffuseTexture;
	Light *_light;

	//Grid stuff
	bool _gridShowing;
	bool _showRange;
	float _gridSize = 5;
	float _lineThiccness = 0.1f;
	float _range = 0;
	glm::vec3 _mousePos;
	glm::vec3 _towerPos;
};

#endif // LitMaterial_HPP
