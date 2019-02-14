#include "glm.hpp"
#include "mge/core/GameController.hpp"
#include <iostream>
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"

std::vector<Light*> GameController::Lights;
std::vector<GameObject*> GameController::GameObjects;
std::vector<GameObject*> GameController::GridObjects;

GameController::GameController() : GameObject("GameController", glm::vec3(0.0f, 0.0f, 0.0f))
{

}

GameController::~GameController()
{

}

