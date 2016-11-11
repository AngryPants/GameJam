#ifndef SCENE_GJ_H
#define SCENE_GJ_H

#include "Scene.h"

class GameObject;

class SceneGJ : public Scene {

private:
	//Variable(s)
	GameObject* camera;
	GameObject* player;
	GameObject* background;

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