#include "SceneGJ.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "RenderSystem.h"
#include "Application.h"
#include "InputManager.h"
#include "GameObjectFactory.h"
#include "MeshBuilder.h"
#include "GameObjectManager.h"

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
	camera->GetComponent<Transform>().SetPosition(0, 0, 5);
	camera->GetComponent<Transform>().SetRotation(0, 180, 0);
	camera->GetComponent<Camera>().aspectRatio.Set(Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight());

	background = &GameObjectFactory::CreateEmpty(name);
	background->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Level 1 Background");
	background->GetComponent<MeshRenderer>().lightEnabled = false;
	background->GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Level 1 Background", "Image//Default//Texture_Test.tga");
	background->AddComponent<Transform>().SetPosition(0, 0, -10);
	background->GetComponent<Transform>().Scale(camera->GetComponent<Camera>().GetOrthoSize() * 0.75f * 3.0f, camera->GetComponent<Camera>().GetOrthoSize() * 2.0f, 1);
	BackgroundScript* backgroundScript = new BackgroundScript();
	background->scripts[0] = backgroundScript;
	backgroundScript->gameObject = background;

	player = &GameObjectFactory::CreatePlayer(name);
	player->GetComponent<Transform>().SetPosition(0, -5, 0);

	GameObjectFactory::CreateBowsir(name, player);
	GameObjectFactory::CreateOctoman(name);
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
	GameObjectManager::GetInstance().UpdateScripts(name, deltaTime);	
	RenderSystem::GetInstance().Update(name, deltaTime);
	//cout << "Number of GameObjects: " << GameObjectManager::GetInstance().GetNumGameObjects(name) << endl;
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