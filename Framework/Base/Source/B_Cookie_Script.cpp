#include "B_Cookie_Script.h"
#include "GameObject.h"
#include "SphereCollider.h"
#include "HealthComponent.h"
#include "GameData.h"

void B_Cookie_Script::Update(double deltaTime) {

	if (bullet == nullptr) {
		return;
	}
	if (!bullet->HasComponent<Transform>()) {
		bullet->AddComponent<Transform>();
	}

	lifeTime -= deltaTime;
	if (lifeTime > 0.0f) {
		Transform& bulletTransform = bullet->GetComponent<Transform>();
		bulletTransform.Translate(bulletTransform.GetUp() * speed * deltaTime);

		SphereCollider& collider = bullet->GetComponent<SphereCollider>();
		for (vector<GameObject*>::iterator vecIter = collider.info.gameObjects.begin(); vecIter != collider.info.gameObjects.end(); ++vecIter) {
			GameObject* go = *vecIter;
			if (go->tag == "Enemy" && go->HasComponent<HealthComponent>() && go->GetComponent<HealthComponent>().IsAlive()) {
				go->GetComponent<HealthComponent>().TakeDamage(damage);
				if (go->GetComponent<HealthComponent>().GetHealth() <= 0) {
					GameData::GetInstance().score += 10;
				}
				bullet->Destroy();
			}
		}
	} else {
		bullet->Destroy();
	}	

}