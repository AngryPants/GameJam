#ifndef BULLET_KICKAC_H
#define BULLET_KICKAC_H

#include "Script.h"

class GameObject;

class B_KicKac_Script : public Script {
	
public:
	//Variable(s)
	GameObject* bullet;
	float lifeTime;
	float speed;
	int damage;

	//Constructor(s) & Destructor
	B_KicKac_Script() {
		bullet = nullptr;
		lifeTime = 5.0f;
		speed = 7.0f;
		damage = 2;
	}
	virtual ~B_KicKac_Script() {}

	//Interface Function(s)
	virtual void Update(double deltaTime);

};

#endif