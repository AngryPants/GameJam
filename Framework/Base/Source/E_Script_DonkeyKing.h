#ifndef E_SCRIPT_DONKEY_KING_H
#define E_SCRIPT_DONKEY_KING_H

#include "Script.h"
#include "Vector3.h"

class GameObject;

class ScriptDonkeyKing : public Script {

private:
	bool initialised;
	Vector3 direction;
	float movementSpeed;
	float lifeTime;
	float hurtPlayerCooldown;
	int damage;

public:
	GameObject* donkeyKing;
	GameObject* player;
	
	ScriptDonkeyKing();
	virtual ~ScriptDonkeyKing();

	void Update(double deltaTime);

};

#endif