#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <string>
#include <iostream>
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world-to-view matrix by taking the inverse of the camera transform.
 * The camera's perspective matrix is used in the MVP matrix creation.
 */
class GameController : public GameObject
{
public:
	GameController();

	virtual ~GameController();
	static std::vector<Light*> Lights;
	static std::vector<GameObject*> GameObjects;
	static std::vector<GameObject*> GridObjects;
private:

private:
	GameController(const GameController&);
	GameController& operator= (const GameController&);
};

#endif // GAMECONTROLLER_HPP