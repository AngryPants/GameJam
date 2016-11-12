#include "E_Script_DonkeyKing.h"
#include "GameObject.h"
#include "SphereCollider.h"
#include "HealthComponent.h"

ScriptDonkeyKing::ScriptDonkeyKing() {
	donkeyKing = nullptr;
	player = nullptr;
	initialised = false;
	movementSpeed = 7.0f;
	lifeTime = 5.0f;
	hurtPlayerCooldown = 0.0f;
	damage = 10;
}

ScriptDonkeyKing::~ScriptDonkeyKing() {
}

void ScriptDonkeyKing::Update(double deltaTime) {
	if (this->donkeyKing == nullptr || this->player == nullptr) {
		return;
	}

	if (initialised == false) {
		donkeyKing->GetComponent<Transform>().SetPosition(0, 20, 0);
		direction = player->GetComponent<Transform>().GetPosition() - donkeyKing->GetComponent<Transform>().GetPosition();
		//donkeyKing->GetComponent<Transform>().SetRotation(0, 0, Math::RadianToDegree(atan2(direction.y, direction.x)));
		donkeyKing->GetComponent<HealthComponent>().SetMaxHealth(50);
		initialised = true;
	}

	lifeTime -= deltaTime;

	if (lifeTime > 0) {
		if (direction.LengthSquared() > Math::EPSILON) {
			direction.Normalize();
		} else {
			direction.Set(0, -1, 0);
		}
		donkeyKing->GetComponent<Transform>().Translate(direction * deltaTime * movementSpeed);
		if (hurtPlayerCooldown > 0.0f) {
			hurtPlayerCooldown -= deltaTime;
		}
		if (hurtPlayerCooldown <= 0.0f) {
			SphereCollider& collider = donkeyKing->GetComponent<SphereCollider>();
			for (vector<GameObject*>::iterator vecIter = collider.info.gameObjects.begin(); vecIter != collider.info.gameObjects.end(); ++vecIter) {
				GameObject* go = *vecIter;
				if (go->tag == "Player" && go->HasComponent<HealthComponent>() && go->GetComponent<HealthComponent>().IsAlive()) {
					go->GetComponent<HealthComponent>().TakeDamage(damage);
					donkeyKing->Destroy();
					hurtPlayerCooldown = 2.0f;
				}
			}			
		}

		if (donkeyKing->GetComponent<HealthComponent>().IsAlive() == false) {
			donkeyKing->Destroy();
		}
	} else {
		donkeyKing->Destroy();
	}
	
}