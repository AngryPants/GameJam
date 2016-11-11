#ifndef B_MEATBALL_SCRIPT_H
#define B_MEATBALL_SCRIPT_H

#include "Script.h"

class GameObject;

class B_Meatball_Script : public Script {

public:
	//Variable(s)
	GameObject* bullet;
	float speed;
	float lifeTime;

	//Constructor(s) & Destructor
	B_Meatball_Script() {
		lifeTime = 5.0f;
		speed = 7.0f;
	}
	virtual ~B_Meatball_Script() {}

	//Interface Function(s)
	virtual void Update(double deltaTime);

};

#endif