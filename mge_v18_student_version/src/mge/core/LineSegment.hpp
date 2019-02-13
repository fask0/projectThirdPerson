#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

#include "mge/core/GameObject.hpp"

#include "glm.hpp"

class LineSegment
{
	public:
	LineSegment(glm::vec3 pPos, glm::vec3 pBoundaries);
	virtual ~LineSegment();
	virtual void update(float pStep);

	GameObject* line;
};

#endif // !LINESEGMENT_HPP
