#include <iostream>

#include "mge/core/LineSegment.hpp"

#include "glm.hpp"

#include "mge/core/Mesh.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/core/AbstractGame.hpp"
#include "mge/core/World.hpp"

#include "mge/config.hpp"

LineSegment::LineSegment(glm::vec3 pPos, glm::vec3 pBoundaries)
{
	Mesh* mesh = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth.obj");
	AbstractMaterial* mat = new ColorMaterial(glm::vec3(0, 1, 0));
	line = new GameObject("line");
	line->scale(pBoundaries);
	line->setLocalPosition(pPos);
	line->setMesh(mesh);
	line->setMaterial(mat);
}

LineSegment::~LineSegment()
{
}

void LineSegment::update(float pStep)
{
}
