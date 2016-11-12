#include "Scene.h"

class GameObject;

class SceneMainMenu : public Scene {

private:
	void InitGameObjects();

public:
	enum MENU_OPTIONS {
		MENU_START,
		MENU_AUDIO,
		MENU_QUIT,
	};

	//Variable(s)
	GameObject* camera;
	GameObject* background;
	GameObject* arrow;
	GameObject* choices;
	GameObject* title;
	GameObject* levelTitle;

	double lvlTitleAnimTime;
	bool startGame;
	bool startAnim;

	MENU_OPTIONS currentState;
	bool keyDown[2];

	//Constructor(s) & Destructor
	SceneMainMenu(const string& name);
	virtual ~SceneMainMenu();
	
	//Virtual Function(s)
	virtual void Init();
	virtual void Save() {}
	virtual void Load() {}
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void Exit();

};