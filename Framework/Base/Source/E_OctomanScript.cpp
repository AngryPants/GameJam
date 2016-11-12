#include "E_OctomanScript.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Transform.h"
#include "InputManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "MyMath.h"
#include "GameData.h"

//Constructor(s) & Destructor
E_OctomanScript::E_OctomanScript() {
	octoman = nullptr;
	movementSpeed = 2.0f;
	moveRotation = 0.f;	
	lifeTime = 10.0f;
	initialised = false;
	hurtPlayerCooldown = 0.0f;
	damage = 12;
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
		float boundaryX = (GameData::GetInstance().worldSizeX + octoman->GetComponent<Transform>().GetScale().x) * 0.3f;
		float boundaryY = (GameData::GetInstance().worldSizeY + octoman->GetComponent<Transform>().GetScale().y) * 0.5f;
		octoman->GetComponent<Transform>().SetRotation(0, 0, -90);
		octoman->GetComponent<Transform>().SetPosition(Math::RandFloatMinMax(-boundaryX, boundaryX), boundaryY + (octoman->GetComponent<Transform>().GetScale().y * 0.5f), 0);
		octoman->GetComponent<HealthComponent>().SetMaxHealth(10);
		octoman->GetComponent<HealthComponent>().SetHealth(10);
	}
	if (lifeTime > 0.0f) {
		while (moveRotation > 360) {
			moveRotation -= 360.0f;
		}
		lifeTime -= deltaTime;
		moveRotation += (float)deltaTime * 2.f;	
		Transform& enemyTransform = octoman->GetComponent<Transform>();
		enemyTransform.Translate(cosf(moveRotation) * deltaTime, -movementSpeed * deltaTime, 0);

		float boundaryX = (GameData::GetInstance().worldSizeX - octoman->GetComponent<Transform>().GetScale().x) * 0.5f;
		float boundaryY = (GameData::GetInstance().worldSizeY + octoman->GetComponent<Transform>().GetScale().y) * 0.5f;
		if (enemyTransform.GetPosition().x > boundaryX) {
			enemyTransform.SetPositionX(-boundaryX);
		} else if (enemyTransform.GetPosition().x < -boundaryX) {
			enemyTransform.SetPositionX(boundaryX);
		}

		if (octoman->GetComponent<HealthComponent>().IsAlive() == false) {
			octoman->Destroy();
		}
		if (hurtPlayerCooldown > 0.0f) {
			hurtPlayerCooldown -= deltaTime;
		}
		if (hurtPlayerCooldown <= 0.0f) {
			SphereCollider& collider = octoman->GetComponent<SphereCollider>();
			for (vector<GameObject*>::iterator vecIter = collider.info.gameObjects.begin(); vecIter != collider.info.gameObjects.end(); ++vecIter) {
				GameObject* go = *vecIter;
				if (go->tag == "Player" && go->HasComponent<HealthComponent>() && go->GetComponent<HealthComponent>().IsAlive()) {
					go->GetComponent<HealthComponent>().TakeDamage(damage);
					hurtPlayerCooldown = 2.0f;
				}
			}			
		}
	} else {
		octoman->Destroy();
	}	
}