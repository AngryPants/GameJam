#ifndef E_BOWSIRSCRIPT_H
#define E_BOWSIRSCRIPT_H

#include "Script.h"
#include "Vector3.h"

class GameObject;

class E_BowsirScript : public Script {

public:
	//Variable(s)	
	GameObject* bowsir;
	GameObject* player;
	float movementSpeed;
	Vector3 target;
	bool reseted;

	//Constructor(s) & Destructor
	E_BowsirScript();
	virtual ~E_BowsirScript();

	//Interface Function(s)
	virtual void Update(const double deltaTime);
	void Reset();
	
};

#endif