#ifndef B_SPINACH_SCRIPT_H
#define B_SPINACH_SCRIPT_H

#include "Script.h"

class GameObject;

class B_Spinach_Script : public Script {

public:
	GameObject* bullet;
	float speed;
	float lifeTime;
	int damage;

	B_Spinach_Script();
	virtual ~B_Spinach_Script();

	virtual void Update(double deltaTime);

};

#endif