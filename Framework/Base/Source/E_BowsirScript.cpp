#include "E_BowsirScript.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Transform.h"
#include "InputManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "MyMath.h"
#include "HealthComponent.h"
#include "GameData.h"

//Constructor(s) & Destructor
E_BowsirScript::E_BowsirScript() {
	bowsir = nullptr;
	player = nullptr;
	movementSpeed = 2.0f;
	initialised = false;
	lifeTime = 6.0f;
	hurtPlayerCooldown = 0.0f;
	damage = 12;
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
		float boundaryX = (GameData::GetInstance().worldSizeX + bowsir->GetComponent<Transform>().GetScale().x) * 0.3f;
		float boundaryY = (GameData::GetInstance().worldSizeY + bowsir->GetComponent<Transform>().GetScale().y) * 0.5f;
		bowsirTransform.SetPosition(Math::RandFloatMinMax(-boundaryX, boundaryX), boundaryY + (bowsir->GetComponent<Transform>().GetScale().y * 0.5f), 0);
		bowsirTransform.SetRotation(0, 0, Math::RadianToDegree(atan2(target.y, target.x)));
	}
	lifeTime -= deltaTime;

	if (lifeTime > 0.0f) {
		bowsirTransform.Translate(target * deltaTime);
		if (hurtPlayerCooldown > 0.0f) {
			hurtPlayerCooldown -= deltaTime;
		}
		if (hurtPlayerCooldown <= 0.0f) {
			SphereCollider& collider = bowsir->GetComponent<SphereCollider>();
			for (vector<GameObject*>::iterator vecIter = collider.info.gameObjects.begin(); vecIter != collider.info.gameObjects.end(); ++vecIter) {
				GameObject* go = *vecIter;
				if (go->tag == "Player" && go->HasComponent<HealthComponent>() && go->GetComponent<HealthComponent>().IsAlive()) {
					go->GetComponent<HealthComponent>().TakeDamage(damage);
					hurtPlayerCooldown = 2.0f;
				}				
			}			
		}

		if (bowsir->GetComponent<HealthComponent>().IsAlive() == false) {
			bowsir->Destroy();
		}
	} else {
		bowsir->Destroy();
	}	
		
}