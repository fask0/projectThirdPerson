#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <string>
#include <iostream>

#include "mge/behaviours/CameraMovementBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Waypoint.hpp"
#include "mge/core/Enemy.hpp"

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
	static std::vector<Enemy*> Enemies;
	static std::vector<GameObject*> GameObjects;
	static std::vector<GameObject*> GridObjects;
	static std::vector<Waypoint*> WaypointsInLevel;

	static Camera* MainCamera;
	static CameraMovementBehaviour* CameraBehaviour;
	static World* World;

	//--Lua variables
	static bool Debug;
	static bool DrawColliders;

	//Toaster tower
	static float ToasterRange;
	static float ToasterAttSpeed;
	static int ToasterCost;
	//Honey tower
	static float HoneyRange;
	static float HoneyAttSpeed;
	static int HoneyCost;
	//MouseTrap tower
	static float MouseTrapRange;
	static int MouseTrapCost;
	//Shock tower
	static float ShockRange;
	static float ShockAttSpeed;
	static int ShockCost;
	//--End of Lua variables

private:
	GameController(const GameController&);
	GameController& operator= (const GameController&);

	void SetTowerVariables();
};

#endif // GAMECONTROLLER_HPP
