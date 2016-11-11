#ifndef E_BOWSIRSCRIPT_H
#define E_BOWSIRSCRIPT_H

#include "Script.h"
#include "Vector3.h"
#include <vector>

using namespace std;
class GameObject;

class E_BowsirScript : public Script {

public:
	//Variable(s)	
	GameObject* bowsir;
	GameObject* player;
	float movementSpeed;
	Vector3 target;
	bool reseted;
	bool startCounting;
	vector<double>v_timer;
	vector<double>::iterator vt;

	//Constructor(s) & Destructor
	E_BowsirScript();
	virtual ~E_BowsirScript();

	//Interface Function(s)
	virtual void Update(const double deltaTime);
	void Reset();
	void Deactivate();
};

#endif