#include <iostream>
#include <string>

#include "glm.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/CameraMovementBehaviour.hpp"
#include "mge/behaviours/CollisionBehaviour.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/LitDynamicGridTextureMaterial.hpp"

#include "mge/core/ToasterTower.hpp"
#include "mge/core/HoneyTower.hpp"
#include "mge/core/MouseTrapTower.hpp"
#include "mge/core/ShockTower.hpp"

#include "mge/core/Waypoint.hpp"
#include "mge/core/EnemySpawner.hpp"

#include "mge/core/Enemy.hpp"
#include "mge/core/Rat.hpp"

#include "mge/core/ToasterProjectile.hpp"

std::vector<Light*> GameController::Lights;
std::vector<Enemy*> GameController::Enemies;
std::vector<GameObject*> GameController::GameObjects;
std::vector<GameObject*> GameController::GridObjects;
std::vector<EnemySpawner*> GameController::SpawnPointsInLevel;
std::vector<Waypoint*> GameController::WaypointsInLevel;

Camera* GameController::MainCamera;
CameraMovementBehaviour* GameController::CameraBehaviour;
World* GameController::World;
sf::RenderWindow* GameController::Window;
UIManager* GameController::UIManager;

//--Lua variables
bool GameController::Debug = false;
bool GameController::DrawColliders;

//Level
//Spawners and Scaling
//Lane A
int GameController::LaneOneBaseSize;
int GameController::LaneOneSizeGrowthFrequency;
int GameController::LaneOneEnemyScalingPercentage;
float GameController::LaneOneDelayBetweenEnemies;
//Lane B
int GameController::LaneTwoBaseSize;
int GameController::LaneTwoSizeGrowthFrequency;
int GameController::LaneTwoEnemyScalingPercentage;
float GameController::LaneTwoDelayBetweenEnemies;
//Lane C
int GameController::LaneThreeBaseSize;
int GameController::LaneThreeSizeGrowthFrequency;
int GameController::LaneThreeEnemyScalingPercentage;
float GameController::LaneThreeDelayBetweenEnemies;
//Lane D
int GameController::LaneFourBaseSize;
int GameController::LaneFourSizeGrowthFrequency;
int GameController::LaneFourEnemyScalingPercentage;
float GameController::LaneFourDelayBetweenEnemies;

//Towers
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

//Enemies
//Rat
int GameController::RatSize;
int GameController::RatHealth;
int GameController::RatHealthRegen;
int GameController::RatDamage;
float GameController::RatSpeed;
float GameController::RatEffectRecoverySpeed;
//--End of Lua variables

GameController::GameController() : GameObject("GameController", glm::vec3(0.0f, 0.0f, 0.0f))
{
}

GameController::~GameController()
{
}

void GameController::Init()
{
	SetTowerVariables();
	SetUpEnemies();
}

void GameController::SetTowerVariables()
{
	AbstractMaterial* mat;

	ToasterProjectile::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/KnifeProjectile");
	ToasterProjectile::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "knife 1.png"));

	//Slingshot tower
	ToasterTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/ToasterTower");
	ToasterTower::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "toaster 1.png"));
	//Honey tower
	HoneyTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/HoneyTower");
	HoneyTower::Material = new LitDynamicTextureGridMaterial(Lights[0], Texture::load(config::MGE_TEXTURE_PATH + "diffuse3.jpg"), true);
	//MouseTrap tower
	MouseTrapTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/MouseTrap");
	MouseTrapTower::Material = new LitDynamicTextureGridMaterial(Lights[0], Texture::load(config::MGE_TEXTURE_PATH + "diffuse2.jpg"), true);
	//Shock tower
	ShockTower::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/AoETower");
	ShockTower::Material = new LitDynamicTextureGridMaterial(Lights[0], Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"), true);
}

void GameController::SetUpEnemies()
{
	//Collider Mesh
	CollisionBehaviour::BoxMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth");
	CollisionBehaviour::SphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere4");

	Rat::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Enemies/Incel");
	Rat::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Enemies/incel.png"));
}