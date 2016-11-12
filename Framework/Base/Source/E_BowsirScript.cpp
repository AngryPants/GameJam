#include "E_BowsirScript.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Transform.h"
#include "InputManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "MyMath.h"
#include "HealthComponent.h"

//Constructor(s) & Destructor
E_BowsirScript::E_BowsirScript() {
	bowsir = nullptr;
	player = nullptr;
	movementSpeed = 2.0f;
	initialised = false;
	lifeTime = 6.0f;
}

E_BowsirScript::~E_BowsirScript() {
}

void E_BowsirScript::Update(double deltaTime) {
	if (bowsir == nullptr) {
		return;
	}
	float boundaryX = 5.0f * 0.75f;
	float boundaryY = 5.0f * 0.8f;
	if (bowsir->HasComponent<Transform>() == false) {
		bowsir->AddComponent<Transform>();
	}
	if (bowsir->HasComponent<HealthComponent>() == false) {
		bowsir->AddComponent<HealthComponent>();
	}
	Transform& bowsirTransform = bowsir->GetComponent<Transform>();
	if (initialised == false) {
		initialised = true;
		if (player != nullptr) {
			target = player->GetComponent<Transform>().GetPosition() - bowsirTransform.GetPosition();
		}
		if (target.LengthSquared() > Math::EPSILON) {
			target.Normalize();
		} else {
			target.Set(1, 0, 0);
		}
		bowsirTransform.SetRotation(0, 0, Math::RadianToDegree(atan2(target.y, target.x)));
	}
	
	bowsirTransform.Translate(target * deltaTime);
	
	if (bowsir->GetComponent<HealthComponent>().IsAlive() == false) {
		bowsir->Destroy();
	}
}