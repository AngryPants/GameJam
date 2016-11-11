#ifndef E_OCTOMANSCRIPT_H
#define E_OCTOMANSCRIPT_H

#include "Script.h"
#include <vector>

using std::vector;

class GameObject;

class E_OctomanScript : public Script {

public:
	//Variable(s)
	float movementSpeed;
	float moveRotation;
	bool reseted;
	bool startCounting;
	vector<double>v_timer;
	vector<double>::iterator vt;

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