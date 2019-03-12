#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "mge/core/GameObject.hpp"

class MenuManager : public GameObject
{
public:
	MenuManager();
	~MenuManager();

	void update(float pStep) override;
};