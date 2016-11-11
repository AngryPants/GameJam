#include "E_OctomanScript.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Transform.h"
#include "InputManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "MyMath.h"

//Constructor(s) & Destructor
E_OctomanScript::E_OctomanScript() {
	octoman = nullptr;
	movementSpeed = 2.0f;
	moveRotation = 0.f;
	reseted = false;
	startCounting = false;
}

E_OctomanScript::~E_OctomanScript() {
}

void E_OctomanScript::Update(double deltaTime) {
	if (octoman == nullptr) {
		return;
	}
	if (reseted == false) {
		Reset();
	}
	if (moveRotation > 180.f) {
		moveRotation = 0.f;
	}		

	if (startCounting == true) {
		*vt -= deltaTime;
		if (*vt <= 0.0) {
			*vt = 0.0;

			if (vt != v_timer.end() - 1) {
				vt++;
			}
			startCounting = false;
			Reset();
		}
	}

	moveRotation += (float)deltaTime * 2.f;
	if (octoman->HasComponent<Transform>() == false) {
		Reset();
	}
	Transform& enemyTransform = octoman->GetComponent<Transform>();
	enemyTransform.Translate(cosf(moveRotation) * deltaTime, -movementSpeed * deltaTime, 0);	
}

void E_OctomanScript::Reset() {
	float boundaryX = 5.0f * 0.65f;
	float boundaryY = 5.0f * 0.8f;
	if (octoman->HasComponent<Transform>() == false) {
		octoman->AddComponent<Transform>().SetPosition(Math::RandFloatMinMax(-boundaryX, boundaryX), boundaryY + 0.5f, 0);
		octoman->GetComponent<Transform>().SetRotation(0, 0, -90);
	}
	reseted = true;
}

void E_OctomanScript::Deactivate() {
	octoman->GetComponent<Transform>().isActive = false;
	startCounting = true;
}