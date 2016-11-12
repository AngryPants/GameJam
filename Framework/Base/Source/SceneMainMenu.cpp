#include "SceneMainMenu.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "RenderSystem.h"
#include "InputManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameData.h"
#include "SceneManager.h"
#include "AudioManager.h"

SceneMainMenu::SceneMainMenu(const string& name) : Scene(name) {
}

SceneMainMenu::~SceneMainMenu() {
}

void SceneMainMenu::InitGameObjects() {
	camera = &GameObjectFactory::CreateCamera(name);
	camera->GetComponent<Camera>().SetOrtho();
	camera->GetComponent<Camera>().SetOrthoSize(GameData::GetInstance().worldSizeY * 0.5f);
	camera->GetComponent<Transform>().SetPosition(0, 0, 5);
	camera->GetComponent<Transform>().SetRotation(0, 180, 0);
	
	background = &GameObjectFactory::CreateBackground(name, "Level 1 Background", "Image//Game_Jam//Background//Grass.tga");
	background->GetComponent<Transform>().Scale(GameData::GetInstance().worldSizeX, GameData::GetInstance().worldSizeY, 1);
	
	arrow = &GameObjectFactory::CreateEmpty(name);
	arrow->AddComponent<Transform>();
	arrow->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Arrow");
	arrow->GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Arrow", "Image//Game_Jam//Menu//Arrow.tga");
	arrow->GetComponent<MeshRenderer>().lightEnabled = false;

	choices = &GameObjectFactory::CreateEmpty(name);
	choices->AddComponent<Transform>().SetPosition(0, -3, 0);
	choices->GetComponent<Transform>().SetScale(5, 3, 1);
	choices->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Choices");
	choices->GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Choices", "Image//Game_Jam//Menu//Choices.tga");
	choices->GetComponent<MeshRenderer>().lightEnabled = false;

	title = &GameObjectFactory::CreateEmpty(name);
	title->AddComponent<Transform>().SetPosition(0, 2, 0);
	title->GetComponent<Transform>().Scale(6, 3, 1);
	title->AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Title");
	title->GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Title", "Image//Game_Jam//Menu//Title.tga");
	title->GetComponent<MeshRenderer>().lightEnabled = false;

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
}

void SceneMainMenu::Init() {
	//Initialise some GraphicsManager stuff.
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::BLENDING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::CULLING>();

	//Initialise the Shader.
	RenderHelper::GetInstance().LoadShader(SHADERS::PHONG);
	RenderHelper::GetInstance().EnableLight(false);
	RenderHelper::GetInstance().SetNumLights(0);
	RenderHelper::GetInstance().EnableFog(false);
	RenderHelper::GetInstance().SetAlphaDiscardValue(0.1f);

	currentState = MENU_START;

	//Initialise the GameObjects.
	InitGameObjects();

	keyDown[0] = false;
	keyDown[1] = false;

	startGame = false;

	AudioManager::GetInstance().PlayAudio2D("Audio//#Music//mainmenu.wav", true);
}

void SceneMainMenu::Update(double deltaTime) {

	if (startGame) {
		bool switchScenes = true;
		if (arrow->GetComponent<Transform>().GetPosition().x > -camera->GetComponent<Camera>().GetOrthoWidth()) {
			arrow->GetComponent<Transform>().Translate(-5.0f * deltaTime, 0, 0);
			switchScenes = false;
		}
		if (choices->GetComponent<Transform>().GetPosition().y > -camera->GetComponent<Camera>().GetOrthoSize() * 1.5f) {
			choices->GetComponent<Transform>().Translate(0, -5.0f * deltaTime, 0);
			switchScenes = false;
		}
		if (title->GetComponent<Transform>().GetPosition().y < camera->GetComponent<Camera>().GetOrthoSize() * 1.5f) {
			title->GetComponent<Transform>().Translate(0, 5.0f * deltaTime, 0);
			switchScenes = false;
		}

		if (switchScenes) {
			SceneManager::GetInstance().SetActiveScene("Level 1");
		}
	} else {
		switch (currentState) {
			case MENU_START: {
				arrow->GetComponent<Transform>().SetPosition(-3, -2, 0);
				break;
			}
			case MENU_AUDIO: {
				arrow->GetComponent<Transform>().SetPosition(-3, -3, 0);
				break;
			}
			case MENU_QUIT: {
				arrow->GetComponent<Transform>().SetPosition(-3, -4, 0);
				break;
			}
		}

		if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_BACKWARD]) {
			if (!keyDown[0]) {
				keyDown[0] = true;
				if (currentState == MENU_START) {
					currentState = MENU_AUDIO;
				} else if (currentState == MENU_AUDIO) {
					currentState = MENU_QUIT;
				}
			}
		} else {
			keyDown[0] = false;
		}

		if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_FORWARD]) {
			if (!keyDown[1]) {
				keyDown[1] = true;
				if (currentState == MENU_QUIT) {
					currentState = MENU_AUDIO;
				} else if (currentState == MENU_AUDIO) {
					currentState = MENU_START;
				}
			}
		} else {
			keyDown[1] = false;
		}

		if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT]) {
			switch (currentState) {
				case MENU_START: {
					startGame = true;
					break;
				}
				case MENU_AUDIO: {
					//Do Audio Studd
					break;
				}
				case MENU_QUIT: {
					Application::GetInstance().Quit();
					break;
				}
			}
		}
	}

	GameObjectManager::GetInstance().UpdateScripts(name, deltaTime);
	RenderSystem::GetInstance().Update(name, deltaTime);
	
	//Close da app
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_QUIT]) {
		Application::GetInstance().Quit();
	}

}

void SceneMainMenu::Render() {
	GraphicsManager::GetInstance().ClearColor();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();

	RenderSystem::GetInstance().Render(name);

	//Render Entities UI
	GraphicsManager::GetInstance().Disable<GraphicsManager::MODE::DEPTH_TEST>();
	GraphicsManager::GetInstance().SetToUI();

	RenderSystem::GetInstance().RenderUI(name);
}

void SceneMainMenu::Exit() {
	RenderHelper::GetInstance().DeleteShader(SHADERS::PHONG);
	GameObjectManager::GetInstance().Clear(name);
}