#ifndef E_OCTOMANSCRIPT_H
#define E_OCTOMANSCRIPT_H

#include "Script.h"

class GameObject;

class E_OctomanScript : public Script {

public:
	//Variable(s)
	float movementSpeed;
	float moveRotation;
	bool reseted;

	GameObject* octoman;

	//Constructor(s) & Destructor
	E_OctomanScript();
	virtual ~E_OctomanScript ();

	//Interface Function(s)
	virtual void Update(const double deltaTime);
	void Reset();
	void Deactivate();

};

#endif