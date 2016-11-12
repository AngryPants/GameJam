#include "B_Meatball_Script.h"
#include "GameObject.h"
#include "Transform.h"
#include "SphereCollider.h"
#include "HealthComponent.h"

void B_Meatball_Script::Update(double deltaTime) {
	if (bullet == nullptr) {
		return;
	}
	if (!bullet->HasComponent<Transform>()) {
		bullet->AddComponent<Transform>();
	}
	lifeTime -= deltaTime;
	if (lifeTime > 0.0f) {
		Transform& bulletTransform = bullet->GetComponent<Transform>();
		bulletTransform.Translate(0, speed * deltaTime, 0);
		bulletTransform.Rotate(0, 0, 800.0f * deltaTime);

		SphereCollider& collider = bullet->GetComponent<SphereCollider>();
		for (vector<GameObject*>::iterator vecIter = collider.info.gameObjects.begin(); vecIter != collider.info.gameObjects.end(); ++vecIter) {
			GameObject* go = *vecIter;
			if (go->tag == "Enemy" && go->HasComponent<HealthComponent>() && go->GetComponent<HealthComponent>().IsAlive()) {
				go->GetComponent<HealthComponent>().TakeDamage(damage);
				bullet->Destroy();
			}
		}
	} else {
		bullet->Destroy();
	}
}