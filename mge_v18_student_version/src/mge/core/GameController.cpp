#include <iostream>
#include "glm.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Enemy.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitTextureMaterial.hpp"

#include "mge/core/ToasterTower.hpp"
#include "mge/core/HoneyTower.hpp"
#include "mge/core/MouseTrapTower.hpp"
#include "mge/core/ShockTower.hpp"

#include "mge/core/ToasterProjectile.hpp"

std::vector<Light*> GameController::Lights;
std::vector<Enemy*> GameController::Enemies;
std::vector<GameObject*> GameController::GameObjects;
std::vector<GameObject*> GameController::GridObjects;
std::vector<Waypoint*> GameController::WaypointsInLevel;

Camera* GameController::MainCamera;
CameraMovementBehaviour* GameController::CameraBehaviour;
World* GameController::World;

//--Lua variables
bool GameController::Debug = false;
bool GameController::DrawColliders;

//Toaster tower
float GameController::ToasterRange;
float GameController::ToasterAttSpeed;
int GameController::ToasterCost;
//Honey tower
float GameController::HoneyRange;
float GameController::HoneyAttSpeed;
int GameController::HoneyCost;
//MouseTrap tower
float GameController::MouseTrapRange;
int GameController::MouseTrapCost;
//Shock tower
float GameController::ShockRange;
float GameController::ShockAttSpeed;
int GameController::ShockCost;
//--End of Lua variables

GameController::GameController() : GameObject("GameController", glm::vec3(0.0f, 0.0f, 0.0f))
{
	SetTowerVariables();
}

GameController::~GameController()
{

}

void GameController::SetTowerVariables()
{
	AbstractMaterial* mat;

	ToasterProjectile::Mesh = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth");
	ToasterProjectile::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "diffuse4.jpg"));

	//Slingshot tower
	ToasterTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat");
	ToasterTower::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
	//Honey tower
	HoneyTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth");
	HoneyTower::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "diffuse3.jpg"));
	//MouseTrap tower
	MouseTrapTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth");
	MouseTrapTower::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "diffuse2.jpg"));
	//Shock tower
	ShockTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth");
	ShockTower::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));
}

