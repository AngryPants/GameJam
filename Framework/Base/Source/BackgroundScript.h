#ifndef BACKGROUND_SCRIPT_H
#define BACKGROUND_SCRIPT_H

#include "Script.h"

class GameObject;

class BackgroundScript : public Script {

public:
	//Variable(s)
	GameObject* gameObject;

	//Constructor(s) & Destructor
	BackgroundScript() {
		gameObject = nullptr;
	}
	virtual ~BackgroundScript() {}

	//Interface Function(s)
	virtual void Update(double deltaTime);

};

#endif