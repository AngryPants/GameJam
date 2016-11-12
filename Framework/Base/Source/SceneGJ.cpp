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
#include "AudioManager.h"

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

	background = &GameObjectFactory::CreateBackground(name, "Level 1 Background", "Image//Game_Jam//Background//Grass.tga");
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
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(10);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(13);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(17);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(22);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(25);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(30);
	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_OCTOMAN].push_back(35);

	spawnerScript->spawnTimes[EnemySpawnerScript::ENEMY_COOKIE_MASTER].push_back(5);

	for (int i = 0; i < 4; ++i) {
		index[i] = nullptr;
	}

	kkIcon = &GameObjectFactory::CreateEmpty(name, "KK Icon");
	kkIcon->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("KK Icon");
	kkIcon->GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("KK Icon", "Image//Game_Jam//Projectile//Projectile_KicKac.tga");
	kkIcon->GetComponent<MeshRenderer>().lightEnabled = false;
	kkIcon->AddComponent<Transform>().SetScale(Vector3(2, 2, 1));
	kkIcon->GetComponent<Transform>().SetPosition(-9, 5, 2);
	

	bananaIcon = &GameObjectFactory::CreateEmpty(name, "Banana Icon");
	bananaIcon->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Banana Icon");
	bananaIcon->GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Banana Icon", "Image//Game_Jam//Projectile//Projectile_Banana.tga");
	bananaIcon->GetComponent<MeshRenderer>().lightEnabled = false;
	bananaIcon->AddComponent<Transform>().SetScale(Vector3(2, 2, 1));
	bananaIcon->GetComponent<Transform>().SetPosition(-9, 2, 2);
	

	cookieIcon = &GameObjectFactory::CreateEmpty(name, "Cookie Icon");
	cookieIcon->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Cookie Icon");
	cookieIcon->GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Cookie Icon", "Image//Game_Jam//Projectile//Projectile_Cookie.tga");
	cookieIcon->GetComponent<MeshRenderer>().lightEnabled = false;
	cookieIcon->AddComponent<Transform>().SetScale(Vector3(1, 1, 1));
	cookieIcon->GetComponent<Transform>().SetPosition(-9, -1, 2);


	meatballIcon = &GameObjectFactory::CreateEmpty(name, "Meatball Icon");
	meatballIcon->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Meatball Icon");
	meatballIcon->GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Meatball Icon", "Image//Game_Jam//Projectile//Projectile_Meatball.tga");
	meatballIcon->GetComponent<MeshRenderer>().lightEnabled = false;
	meatballIcon->AddComponent<Transform>().SetScale(Vector3(1, 1, 1));
	meatballIcon->GetComponent<Transform>().SetPosition(-9, -4, 2);


	index[0] = &GameObjectFactory::CreateEmpty(name, "KK icon num");
	index[0]->AddComponent<TextRenderer>().text = "1";
	index[0]->GetComponent<TextRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("KK icon num", "Image//Fonts//Consolas.tga");
	index[0]->GetComponent<TextRenderer>().mesh = MeshBuilder::GetInstance().GenerateText("KK icon num", 16, 16);
	index[0]->GetComponent<TextRenderer>().textColor.Set(1, 1, 1);
	index[0]->AddComponent<Transform>().SetScale(Vector3(2, 2, 1));
	index[0]->GetComponent<Transform>().SetPosition(-7, 5, 2);


	index[1] = &GameObjectFactory::CreateEmpty(name, "Banana icon num");
	index[1]->AddComponent<TextRenderer>().text = "2";
	index[1]->GetComponent<TextRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Banana icon num", "Image//Fonts//Consolas.tga");
	index[1]->GetComponent<TextRenderer>().mesh = MeshBuilder::GetInstance().GenerateText("Banana icon num", 16, 16);
	index[1]->GetComponent<TextRenderer>().textColor.Set(1, 1, 1);
	index[1]->AddComponent<Transform>().SetScale(Vector3(2, 2, 1));
	index[1]->GetComponent<Transform>().SetPosition(-7, 2, 2);


	index[2] = &GameObjectFactory::CreateEmpty(name, "Cookie icon num");
	index[2]->AddComponent<TextRenderer>().text = "3";
	index[2]->GetComponent<TextRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Cookie icon num", "Image//Fonts//Consolas.tga");
	index[2]->GetComponent<TextRenderer>().mesh = MeshBuilder::GetInstance().GenerateText("Cookie icon num", 16, 16);
	index[2]->GetComponent<TextRenderer>().textColor.Set(1, 1, 1);
	index[2]->AddComponent<Transform>().SetScale(Vector3(2, 2, 1));
	index[2]->GetComponent<Transform>().SetPosition(-7, -1, 2);


	index[3] = &GameObjectFactory::CreateEmpty(name, "Meatball icon num");
	index[3]->AddComponent<TextRenderer>().text = "4";
	index[3]->GetComponent<TextRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Meatball icon num", "Image//Fonts//Consolas.tga");
	index[3]->GetComponent<TextRenderer>().mesh = MeshBuilder::GetInstance().GenerateText("Meatball icon num", 16, 16);
	index[3]->GetComponent<TextRenderer>().textColor.Set(1, 1, 1);
	index[3]->AddComponent<Transform>().SetScale(Vector3(2, 2, 1));
	index[3]->GetComponent<Transform>().SetPosition(-7, -4, 2);

	scoreText = &GameObjectFactory::CreateEmpty(name, "ScoreText");
	scoreText->AddComponent<TextRenderer>().text = "SCORE";
	scoreText->GetComponent<TextRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("ScoreText", "Image//Fonts//Consolas.tga");
	scoreText->GetComponent<TextRenderer>().mesh = MeshBuilder::GetInstance().GenerateText("ScoreText", 16, 16);
	scoreText->GetComponent<TextRenderer>().textColor.Set(1, 1, 1);
	scoreText->AddComponent<Transform>().SetScale(Vector3(1, 1, 1));
	scoreText->GetComponent<Transform>().SetPosition(5.6f, 5, 2);

	score = &GameObjectFactory::CreateEmpty(name, "Score");
	score->AddComponent<TextRenderer>().text = to_string(GameData::GetInstance().score);
	score->GetComponent<TextRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Score", "Image//Fonts//Consolas.tga");
	score->GetComponent<TextRenderer>().mesh = MeshBuilder::GetInstance().GenerateText("Score", 16, 16);
	score->GetComponent<TextRenderer>().textColor.Set(1, 1, 1);
	score->AddComponent<Transform>().SetScale(Vector3(0.5, 0.5, 1));
	score->GetComponent<Transform>().SetPosition(8, 4, 2);
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
	AudioManager::GetInstance().PlaySoleAudio2D("Audio//Music//level1.wav", true);
}

void SceneGJ::Update(double deltaTime) {	
	CollisionSystem::GetInstance().Reset(name);
	CollisionSystem::GetInstance().CheckCollision(name, deltaTime);
	GameObjectManager::GetInstance().UpdateScripts(name, deltaTime);
	RenderSystem::GetInstance().Update(name, deltaTime);
	score->GetComponent<TextRenderer>().text = to_string(GameData::GetInstance().score);

	//cout << "Number of GameObjects: " << GameObjectManager::GetInstance().GetNumGameObjects(name) << endl;
	//cout << "FPS: " << to_string(1.0/deltaTime) << endl;
	//Close da app
	//if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_QUIT]) {
	//	Application::GetInstance().Quit();
	//}
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