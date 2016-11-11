#ifndef PLAYER_CONTROL_SCRIPT_H
#define PLAYER_CONTROL_SCRIPT_H

#include "Script.h"

class GameObject;

class PlayerControlScript : public Script {

private:
	//Variable(s)
	void ShootKicKac();
	void ShootBanana();
	void ShootCookie();
	void ShootMeatball();
	double fireRate;
	double timeToFire;

public:
	//Enum(s)
	enum PLAYER_FORM {
		FORM_DEFAULT,
		FORM_OCTOMAN,
		FORM_DONKEY_KING,
		FORM_COOKIE_MASTER,
		FORM_BOWSIR,
		NUM_FORM,
	};

	bool unlockForms[NUM_FORM];
	PLAYER_FORM currentForm;

	//Variable(s)
	float movementSpeed;
	GameObject* player;

	//Constructor(s) & Destructor
	PlayerControlScript();
	virtual ~PlayerControlScript();

	//Interface Function(s)
	virtual void Update(double deltaTime);

};

#endif