#ifndef B_COOKIE_SCRIPT_H
#define B_COOKIE_SCRIPT_H

#include "Script.h"

class GameObject;

class B_Cookie_Script : public Script {
	
public:
	//Variable(s)
	GameObject* bullet;
	float speed;
	float lifeTime;

	//Constructor(s) & Destructor
	B_Cookie_Script() {
		lifeTime = 5.0f;
		speed = 10.0f;
		bullet = nullptr;
	}
	virtual ~B_Cookie_Script() {}

	//Interface Function(s)
	virtual void Update(double deltaTime);

};

#endif