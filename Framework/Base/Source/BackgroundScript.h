#ifndef BACKGROUND_SCRIPT_H
#define BACKGROUND_SCRIPT_H

#include "Script.h"

class GameObject;

class BackgroundScript : public Script {

public:
	//Variable(s)
	GameObject* gameObject;
	float scrollSpeed;

	//Constructor(s) & Destructor
	BackgroundScript() {
		scrollSpeed = 0.6f;
		gameObject = nullptr;
	}
	virtual ~BackgroundScript() {}

	//Interface Function(s)
	virtual void Update(double deltaTime);

};

#endif