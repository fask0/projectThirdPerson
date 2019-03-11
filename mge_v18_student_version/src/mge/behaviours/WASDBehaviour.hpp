#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"

class WASDBehaviour : public AbstractBehaviour
{
public:
	WASDBehaviour();
	virtual ~WASDBehaviour();

	virtual void update(float pstep);

};
