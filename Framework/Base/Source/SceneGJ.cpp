#include "SceneGJ.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "RenderSystem.h"
#include "Application.h"
#include "InputManager.h"
#include "GameObjectFactory.h"
#include "MeshBuilder.h"
#include "GameObjectManager.h"
#include "CollisionSystem.h"
#include "GameData.h"

//Include Components
#include "SpriteRenderer.h"

//Include Scripts
#include "BackgroundScript.h"
#include "PlayerControlScript.h"

//Constructor(s) & Destructor
SceneGJ::SceneGJ(const string& name) : Scene(name) {
}

SceneGJ::~SceneGJ() {
}

//Virtual Function(s)
void SceneGJ::InitGameObjects() {
	
	camera = &GameObjectFactory::CreateCamera(name);
	camera->GetComponent<Camera>().SetOrtho();
	camera->GetComponent<Camera>().SetOrthoSize(GameData::GetInstance().worldSizeY * 0.5f);
	camera->GetComponent<Transform>().SetPosition(0, 0, 5);
	camera->GetComponent<Transform>().SetRotation(0, 180, 0);
	camera->GetComponent<Camera>().aspectRatio.Set(Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight());

	background = &GameObjectFactory::CreateBackground(name, "Level 1 Background", "Image//Game_Jam//Background//Water.tga");
	background->GetComponent<Transform>().Scale(GameData::GetInstance().worldSizeX, GameData::GetInstance().worldSizeY, 1);

	//Black Bars
	{
		Vector3 scale(camera->GetComponent<Camera>().GetOrthoWidth() - (GameData::GetInstance().worldSizeX * 0.5f), GameData::GetInstance().worldSizeY, 1);
		GameObject* bar1 = &GameObjectFactory::CreateEmpty(name, "Black Bar");
		bar1->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Black Bar", Color(0, 0, 0), 1);		
		bar1->AddComponent<Transform>().SetScale(scale);
		bar1->GetComponent<Transform>().SetPosition(-0.5f * (scale.x + GameData::GetInstance().worldSizeX), 0, 1);

		GameObject* bar2 = &GameObjectFactory::CreateEmpty(name, "Black Bar");
		bar2->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Black Bar", Color(0, 0, 0), 1);
		bar2->AddComponent<Transform>().SetScale(scale);
		bar2->GetComponent<Transform>().SetPosition(0.5f * (scale.x + GameData::GetInstance().worldSizeX), 0, 1);
	}

	player = &GameObjectFactory::CreatePlayer(name);
	player->GetComponent<Transform>().SetPosition(0, -5, 0);

	GameObjectFactory::CreateBowsir(name, player);
	GameObjectFactory::CreateOctoman(name);

	spawner = &GameObjectFactory::CreateSpawner(name, "Spawner", player);
	EnemySpawnerScript* spawnerScript = static_cast<EnemySpawnerScript*>(spawner->scripts[0]);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(0.5);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(5);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(8);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(12);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(20);

}

void SceneGJ::Init() {
	//Initialise some GraphicsManager stuff.
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::BLENDING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::CULLING>();

	//Initialise the Shader.
	RenderHelper::GetInstance().LoadShader(SHADERS::PHONG);
	RenderHelper::GetInstance().EnableLight(false);
	RenderHelper::GetInstance().SetNumLights(0);
	RenderHelper::GetInstance().EnableFog(false);
	RenderHelper::GetInstance().SetAlphaDiscardValue(0.1f);

	//Initialise the GameObjects.
	InitGameObjects();
}

void SceneGJ::Update(double deltaTime) {	
	CollisionSystem::GetInstance().Reset(name);
	CollisionSystem::GetInstance().CheckCollision(name, deltaTime);
	GameObjectManager::GetInstance().UpdateScripts(name, deltaTime);
	RenderSystem::GetInstance().Update(name, deltaTime);
	cout << "Number of GameObjects: " << GameObjectManager::GetInstance().GetNumGameObjects(name) << endl;
	cout << "FPS: " << to_string(1.0/deltaTime) << endl;
	//Close da app
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_QUIT]) {
		Application::GetInstance().Quit();
	}
}

void SceneGJ::Render() {
	GraphicsManager::GetInstance().ClearColor();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();

	RenderSystem::GetInstance().Render(name);

	//Render Entities UI
	GraphicsManager::GetInstance().Disable<GraphicsManager::MODE::DEPTH_TEST>();
	GraphicsManager::GetInstance().SetToUI();

	RenderSystem::GetInstance().RenderUI(name);
}

void SceneGJ::Exit() {
	RenderHelper::GetInstance().DeleteShader(SHADERS::PHONG);
	GameObjectManager::GetInstance().Clear(name);
}