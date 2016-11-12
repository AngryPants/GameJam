#ifndef GAMEOBJECT_FACTORY_H
#define GAMEOBJECT_FACTORY_H

#include "GameObject.h"

//Include Systems
#include "TextureManager.h"
#include "MeshBuilder.h"

//Include Scripts
#include "PlayerControlScript.h"
#include "BackgroundScript.h"
#include "B_KicKac_Script.h"
#include "B_Banana_Script.h"
#include "B_Cookie_Script.h"
#include "B_Meatball_Script.h"
#include "E_BowsirScript.h"
#include "E_OctomanScript.h"
#include "EnemySpawnerScript.h"

//Include Components
#include "Camera.h"
#include "Transform.h"
#include "Light.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "HealthComponent.h"
#include "SphereCollider.h"

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
		go.tag = "Player";
		go.AddComponent<Transform>().SetScale(0.5, 0.5, 0.5);
		go.AddComponent<SpriteRenderer>().SetSpriteAnimation(*MeshBuilder::GetInstance().GenerateSpriteAnimation("Player", 4, 4));
		Animation animation(4, 4, 0, 15, true, 0.5, true);
		go.GetComponent<SpriteRenderer>().AddAnimation("Default", animation);
		go.GetComponent<SpriteRenderer>().SetAnimation("Default");
		go.GetComponent<SpriteRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Octoman", "Image//Game_Jam//Character//Sprite_Octoman.tga");
		PlayerControlScript* script = new PlayerControlScript();
		go.scripts[0] = script;
		script->player = &go;

		return go;
	}

	static GameObject& CreateKicKac(const string& space, const string& name = "Kic Kac") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.tag = "Player Bullet";
		float radius = 0.15;
		go.AddComponent<SphereCollider>().SetRadius(radius);
		go.AddComponent<Transform>().SetScale(radius * 2.0f, radius * 2.0f, radius * 2.0f);
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
		go.tag = "Bullet Banana";
		float radius = 0.15;
		go.AddComponent<SphereCollider>().SetRadius(radius);
		go.AddComponent<Transform>().SetScale(radius * 2.0f, radius * 2.0f, radius * 2.0f);
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
		go.tag = "Bullet Cookie";
		float radius = 0.15;
		go.AddComponent<SphereCollider>().SetRadius(radius);
		go.AddComponent<Transform>().SetScale(radius * 2.0f, radius * 2.0f, radius * 2.0f);
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
		go.tag = "Bullet Meatball";
		float radius = 0.05;
		go.AddComponent<SphereCollider>().SetRadius(radius);
		go.AddComponent<Transform>().SetScale(radius * 2.0f, radius * 2.0f, radius * 2.0f);
		go.AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad("Meatball");
		go.GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Meatball", "Image//Game_Jam//Projectile//Projectile_Meatball.tga");
		go.GetComponent<MeshRenderer>().lightEnabled = false;

		B_Meatball_Script* script = new B_Meatball_Script();
		script->bullet = &go;
		go.scripts[0] = script;

		return go;
	}

	static GameObject& CreateBowsir(const string& space, GameObject* player, const string& name = "Bowsir") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.tag = "Enemy";
		//go.AddComponent<Transform>();
		go.AddComponent<HealthComponent>().SetHealth(10);
		go.AddComponent<SpriteRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Bowsir", "Image//Game_Jam//Character//Sprite_Bowsir.tga");
		go.GetComponent<SpriteRenderer>().SetSpriteAnimation(*MeshBuilder::GetInstance().GenerateSpriteAnimation("Bowsir", 2, 3));
		Animation animationLeft(2, 3, 0, 2, true, 0.5, true);
		Animation animationRight(2, 3, 3, 5, true, 0.5, true);
		go.GetComponent<SpriteRenderer>().AddAnimation("Move Right", animationRight);
		go.GetComponent<SpriteRenderer>().AddAnimation("Move Left", animationLeft);
		go.GetComponent<SpriteRenderer>().SetAnimation("Move Right");
		go.GetComponent<SpriteRenderer>().lightEnabled = false;
		go.AddComponent<SphereCollider>();

		E_BowsirScript* script = new E_BowsirScript();
		script->bowsir = &go;
		script->player = player;
		go.scripts[0] = script;

		return go;
	}

	static GameObject& CreateOctoman(const string& space, const string& name = "Octoman") {
		GameObject& go = GameObjectManager::GetInstance().CreateGameObject(space, name);
		go.tag = "Enemy";
		//go.AddComponent<Transform>();
		go.AddComponent<HealthComponent>().SetHealth(5);
		go.AddComponent<SpriteRenderer>().SetSpriteAnimation(*MeshBuilder::GetInstance().GenerateSpriteAnimation("Player", 4, 4));
		Animation animation(4, 4, 3, 2, true, 0.5, true);
		go.GetComponent<SpriteRenderer>().AddAnimation("Default", animation);
		go.GetComponent<SpriteRenderer>().SetAnimation("Default");
		go.GetComponent<SpriteRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture("Octoman", "Image//Game_Jam//Character//Sprite_Octoman.tga");
		go.AddComponent<SphereCollider>();

		E_OctomanScript* script = new E_OctomanScript();
		script->octoman = &go;
		go.scripts[0] = script;

		return go;
	}

	static GameObject& CreateBackground(const string& space, const string& name, const string& filePath) {
		GameObject& go = GameObjectFactory::CreateEmpty(space);
		go.AddComponent<MeshRenderer>().mesh = MeshBuilder::GetInstance().GenerateQuad(name);
		go.GetComponent<MeshRenderer>().lightEnabled = false;
		go.GetComponent<MeshRenderer>().textureList.textureArray[0] = TextureManager::GetInstance().AddTexture(name, filePath);
		go.AddComponent<Transform>().SetPosition(0, 0, -10);		
		BackgroundScript* script = new BackgroundScript();
		go.scripts[0] = script;
		script->gameObject = &go;

		return go;
	}

	static GameObject& CreateSpawner(const string& space, const string& name = "Spawner", GameObject* player = nullptr) {
		GameObject& go = GameObjectFactory::CreateEmpty(space);
		EnemySpawnerScript* script = new EnemySpawnerScript();
		script->spawner = &go;
		script->player = player;
		go.scripts[0] = script;

		return go;
	}

};

#endif