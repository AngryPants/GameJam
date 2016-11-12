#ifndef E_COOKIE_MASTER_H
#define E_COOKIE_MASTER_H

#include "Script.h"
#include <vector>
#include "Vector3.h"

using std::vector;

class GameObject;

class E_Cookie_Master : public Script {

private:
	bool initialised;
	float lifeTime;
	float timeToShoot;
	float fireRate;

	void Shoot();

public:
	GameObject* cookieMaster;
	float movementSpeed;
	
	E_Cookie_Master();
	virtual ~E_Cookie_Master();

	virtual void Update(double deltaTime);

};

#endif