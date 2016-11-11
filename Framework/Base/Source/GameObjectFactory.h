#ifndef GAMEOBJECT_FACTORY_H
#define GAMEOBJECT_FACTORY_H

#include "GameObject.h"

//Include Systems
#include "TextureManager.h"
#include "MeshBuilder.h"

//Include Scripts
#include "PlayerControlScript.h"
#include "B_KicKac_Script.h"
#include "B_Banana_Script.h"
#include "B_Cookie_Script.h"
#include "B_Meatball_Script.h"

//Include Components
#include "Camera.h"
#include "Transform.h"
#include "Light.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

class GameObjectFactory {

public:
	GameObjectFactory() {}
	virtual ~GameObjectFactory() {}

	static GameObject& CreateCamera(const string& space, const string& name = "Camera") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.AddComponent<Camera>();
		go.AddComponent<Transform>();

		return go;
	}

	static GameObject& CreateLight(const string& space, const string& name = "Light") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.AddComponent<Light>();
		go.AddComponent<Transform>();

		return go;
	}

	static GameObject& CreateEmpty(const string& space, const string& name = "GameObject") {
		return GameObjectManager::GetInstance().CreateGameObject(space, name);
	}

	static GameObject& CreatePlayer(const string& space, const string& name = "Player") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.AddComponent<Transform>().SetScale(0.5, 0.5, 0.5);
		go.AddComponent<SpriteRenderer>().mesh = MeshBuilder::GetInstance().GenerateSpriteAnimation("go", 4, 4);
		Animation octomanAnim(4, 4, 3, 2, true, 0.5, true);
		go.GetComponent<SpriteRenderer>().animations.insert(std::pair<string, Animation>("Octoman", octomanAnim));
		go.GetComponent<SpriteRenderer>().mesh->animation = &go.GetComponent<SpriteRenderer>().animations.find("Octoman")->second;
		go.GetComponent<SpriteRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Octoman", "Image//Game_Jam//Character//Sprite_Octoman.tga");
		PlayerControlScript* script = new PlayerControlScript();
		go.scripts[0] = script;
		script->player = &go;

		return go;
	}

	static GameObject& CreateKicKac(const string& space, const string& name = "Kic Kac") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.tag = "Player Bullet";
		go.AddComponent<Transform>().SetScale(0.3f, 0.3f, 0.3f);
		go.AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Kic Kac");
		go.GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Kic Kac", "Image//Game_Jam//Projectile//Projectile_KicKac.tga");
		go.GetComponent<MeshRenderer>().lightEnabled = false;

		B_KicKac_Script* script = new B_KicKac_Script();
		script->bullet = &go;
		go.scripts[0] = script;

		return go;
	}

	static GameObject& CreateBanana(const string& space, const string& name = "Banana") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.tag = "Player Bullet";
		go.AddComponent<Transform>().SetScale(0.3f, 0.3f, 0.3f);
		go.AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Banana");
		go.GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Banana", "Image//Game_Jam//Projectile//Projectile_Banana.tga");
		go.GetComponent<MeshRenderer>().lightEnabled = false;

		B_Banana_Script* script = new B_Banana_Script();
		script->bullet = &go;
		go.scripts[0] = script;

		return go;
	}

	static GameObject& CreateCookie(const string& space, const string& name = "Cookie") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.tag = "Player Bullet";
		go.AddComponent<Transform>().SetScale(0.3f, 0.3f, 0.3f);
		go.AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Cookie");
		go.GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Cookie", "Image//Game_Jam//Projectile//Projectile_Cookie.tga");
		go.GetComponent<MeshRenderer>().lightEnabled = false;

		B_Cookie_Script* script = new B_Cookie_Script();
		script->bullet = &go;
		go.scripts[0] = script;

		return go;
	}

	static GameObject& CreateMeatball(const string& space, const string& name = "Meatball") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.tag = "Player Bullet";
		go.AddComponent<Transform>().SetScale(0.5f, 0.5f, 0.5f);
		go.AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Meatball");
		go.GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Meatball", "Image//Game_Jam//Projectile//Projectile_Meatball.tga");
		go.GetComponent<MeshRenderer>().lightEnabled = false;

		B_Meatball_Script* script = new B_Meatball_Script();
		script->bullet = &go;
		go.scripts[0] = script;

		return go;
	}

};

#endif