#ifndef SCENE_GJ_H
#define SCENE_GJ_H

#include "Scene.h"
#include "TextureList.h"

class GameObject;
class Mesh;

class SceneGJ : public Scene {

private:
	//Variable(s)
	GameObject* camera;
	GameObject* player;
	GameObject* background;
	GameObject* spawner;

	GameObject* kkIcon;
	GameObject* bananaIcon;
	GameObject* meatballIcon;
	GameObject* cookieIcon;

	GameObject* index[4];
	GameObject* scoreText;
	GameObject* score;

	Mesh* hpBar;
	Mesh* hpText;
	TextureList textureList;


	//Private Function(s)
	void InitGameObjects();

public:
	//Constructor(s) & Destructor
	SceneGJ(const string& name);
	virtual ~SceneGJ();
	
	//Virtual Function(s)
	virtual void Init();
	virtual void Save() {}
	virtual void Load() {}
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif