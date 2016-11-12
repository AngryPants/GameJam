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
	lifeTime = 10.0f;
	initialised = false;
}

E_OctomanScript::~E_OctomanScript() {
}

void E_OctomanScript::Update(double deltaTime) {
	if (octoman == nullptr) {
		return;
	}
	if (octoman->HasComponent<Transform>() == false) {
		octoman->AddComponent<Transform>();
	}
	if (octoman->HasComponent<HealthComponent>() == false) {
		octoman->AddComponent<HealthComponent>();
	}
	if (initialised == false) {
		initialised = true;
		float boundaryX = 5.0f * 0.65f;
		float boundaryY = 5.0f * 0.8f;
		octoman->GetComponent<Transform>().SetRotation(0, 0, -90);
		octoman->GetComponent<Transform>().SetPosition(Math::RandFloatMinMax(-boundaryX, boundaryX), boundaryY + 0.5f, 0);
		octoman->GetComponent<HealthComponent>().SetHealth(10);
	}
	if (lifeTime > 0.0f) {
		while (moveRotation > 180.f) {
			moveRotation -= 180.0f;
		}	
		lifeTime -= deltaTime;
		moveRotation += (float)deltaTime * 2.f;	
		Transform& enemyTransform = octoman->GetComponent<Transform>();
		enemyTransform.Translate(cosf(moveRotation) * deltaTime, -movementSpeed * deltaTime, 0);

		if (octoman->GetComponent<HealthComponent>().IsAlive() == false) {
			octoman->Destroy();
		}
	} else {
		octoman->Destroy();
	}	
}