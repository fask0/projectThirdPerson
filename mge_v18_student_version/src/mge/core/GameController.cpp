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
#include "mge/core/ChadRat.hpp"
#include "mge/core/SanicRat.hpp"

#include "mge/core/ToasterProjectile.hpp"
#include "mge/core/HoneyProjectile.hpp"

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
GridManager* GameController::GridManager;

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
int GameController::StartingMoney;
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
//ChadRat
int GameController::ChadSize;
int GameController::ChadHealth;
int GameController::ChadHealthRegen;
int GameController::ChadDamage;
float GameController::ChadSpeed;
float GameController::ChadEffectRecoverySpeed;
//SanicRat
int GameController::SanicSize;
int GameController::SanicHealth;
int GameController::SanicHealthRegen;
int GameController::SanicDamage;
float GameController::SanicSpeed;
float GameController::SanicEffectRecoverySpeed;
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
	HoneyProjectile::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Towers/KnifeProjectile");
	HoneyProjectile::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "knife 1.png"));

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

	//Rat
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie0"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie1"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie2"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie3"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie4"));
	Rat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Normie/normie5"));
	Rat::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Enemies/incel.png"));
	//ChadRat
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad0"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad1"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad2"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad3"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad4"));
	ChadRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/Chad/chad5"));
	ChadRat::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Enemies/chad_texture.png"));
	//SanicRat
	//SanicRat::Mesh = Mesh::load(config::MGE_MODEL_PATH + "Enemies/fastboi");
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi0"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi1"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi2"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi3"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi4"));
	SanicRat::Animation.push_back(Mesh::load(config::MGE_MODEL_PATH + "Enemies/FastBoi/fastboi5"));
	SanicRat::Material = new LitTextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Enemies/fastboi_texture.png"));
}