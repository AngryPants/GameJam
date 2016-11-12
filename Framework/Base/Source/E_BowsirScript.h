#ifndef E_BOWSIRSCRIPT_H
#define E_BOWSIRSCRIPT_H

#include "Script.h"
#include "Vector3.h"
#include <vector>

using namespace std;
class GameObject;

class E_BowsirScript : public Script {

private:
	bool initialised;
	float lifeTime;

public:
	//Variable(s)	
	GameObject* bowsir;
	GameObject* player;
	float movementSpeed;
	Vector3 target;

	//Constructor(s) & Destructor
	E_BowsirScript();
	virtual ~E_BowsirScript();

	//Interface Function(s)
	virtual void Update(double deltaTime);
};

#endif