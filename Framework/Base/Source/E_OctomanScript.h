#ifndef E_OCTOMANSCRIPT_H
#define E_OCTOMANSCRIPT_H

#include "Script.h"
#include "Vector3.h"
#include <vector>

using std::vector;

class GameObject;

class E_OctomanScript : public Script {

private:
	//Movement
	float movementSpeed;
	float moveRotation;

	//Spawning
	float lifeTime;
	bool initialised;

public:
	//Variable(s)	
	//vector<Vector3>waypoints;
	GameObject* octoman;

	//Constructor(s) & Destructor
	E_OctomanScript();
	virtual ~E_OctomanScript ();

	//Interface Function(s)
	virtual void Update(const double deltaTime);

};

#endif