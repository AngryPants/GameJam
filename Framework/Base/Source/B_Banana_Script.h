#ifndef B_BANANA_SCRIPT_H
#define B_BANANA_SCRIPT_H

#include "Script.h"

class GameObject;

class B_Banana_Script : public Script {

public:
	//Variable(s)
	GameObject* bullet;
	double lifeTime;
	float speed;
	float positionOffset;
	float scaleIncrease;
	int damage;

	//Constructor(s) & Destructor
	B_Banana_Script() {
		bullet = nullptr;
		lifeTime = 5.0f;
		speed = 4.0f;
		positionOffset = 0.0f;
		scaleIncrease = 0.0f;
		damage = 5;
	}
	virtual ~B_Banana_Script() {}

	//Interface Function(s)
	virtual void Update(double deltaTime);

};

#endif