#include "glm.hpp"
#include "mge/core/GameController.hpp"
#include <iostream>
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/CameraMovementBehaviour.hpp"

std::vector<Light*> GameController::Lights;
std::vector<GameObject*> GameController::GameObjects;
std::vector<GameObject*> GameController::GridObjects;
std::vector<Waypoint*> GameController::WaypointsInLevel;

Camera* GameController::MainCamera;
CameraMovementBehaviour* GameController::CameraBehaviour;

<<<<<<< HEAD
//Lua variables
bool GameController::Debug = false;
=======
bool GameController::DrawColliders;
>>>>>>> 7e40c7fd5fe4f50d1117a01501a39e7369afaae0

GameController::GameController() : GameObject("GameController", glm::vec3(0.0f, 0.0f, 0.0f))
{

}

GameController::~GameController()
{

}

