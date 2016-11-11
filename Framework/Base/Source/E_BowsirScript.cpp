#include "E_BowsirScript.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Transform.h"
#include "InputManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "MyMath.h"

//Constructor(s) & Destructor
E_BowsirScript::E_BowsirScript() {
	bowsir = nullptr;
	player = nullptr;
	movementSpeed = 2.0f;
	reseted = false;
	startCounting = false;
	v_timer.clear();
	vt = v_timer.begin();
}

E_BowsirScript::~E_BowsirScript() {
}

void E_BowsirScript::Update(double deltaTime) {
	if (bowsir == nullptr) {
		return;
	}
	if (reseted == false) {
		Reset();
	}
	float boundaryX = 5.0f * 0.75f;
	float boundaryY = 5.0f * 0.8f;
	if (bowsir->HasComponent<Transform>() == false) {
		Reset();
	}
	
	if (startCounting == true) {
		*vt -= deltaTime;
		if (*vt <= 0.0) {
			*vt = 0.0;

			if (vt != v_timer.end()- 1) {
				vt++;
			}
			startCounting = false;
			Reset();
		}
	}

	Transform& enemyTransform = bowsir->GetComponent<Transform>();
	if (target.LengthSquared() > Math::EPSILON) {
		target.Normalize();
	} else {
		target.Set(1, 0, 0);
	}
	enemyTransform.Translate(target * deltaTime);
	enemyTransform.SetRotation(0, 0, Math::RadianToDegree(atan2(target.y, target.x)));
}

void E_BowsirScript::Reset() {
	if (bowsir->HasComponent<Transform>() == false) {
		bowsir->AddComponent<Transform>();
	}
	float boundaryX = 5.0f * 0.75f;
	float boundaryY = 5.0f * 0.8f;
	Transform& enemyTransform = bowsir->GetComponent<Transform>();
	enemyTransform.SetPosition(Math::RandFloatMinMax(-boundaryX, boundaryX), boundaryY + 0.5f, 0);	
	if (player != nullptr && player->HasComponent<Transform>()) {
		target = player->GetComponent<Transform>().GetPosition() - enemyTransform.GetPosition();
	}
	enemyTransform.SetRotation(0, 0, Math::RadianToDegree(atan2(target.y, target.x)));
	reseted = true;
}

void E_BowsirScript::Deactivate() {
	bowsir->GetComponent<Transform>().isActive = false;
	startCounting = true;
}