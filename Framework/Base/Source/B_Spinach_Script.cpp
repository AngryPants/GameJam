#include "B_Spinach_Script.h"
#include "Transform.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "SphereCollider.h"

B_Spinach_Script::B_Spinach_Script() {
	bullet = nullptr;
	speed = 2.0f;
	damage = 3;
}

B_Spinach_Script::~B_Spinach_Script() {
}

void B_Spinach_Script::Update(double deltaTime) {
	if (bullet == nullptr) {
		return;
	}
	if (bullet->HasComponent<Transform>() == false) {
		return;
	}
	if (bullet->HasComponent<SphereCollider>() == false) {
		return;
	}

	Transform& bulletTransform = bullet->GetComponent<Transform>();
	bulletTransform.Translate(bulletTransform.GetUp() * deltaTime * speed);
	//bulletTransform.Translate(0, -1 * deltaTime, 0);

	SphereCollider& collider = bullet->GetComponent<SphereCollider>();
	for (vector<GameObject*>::iterator vecIter = collider.info.gameObjects.begin(); vecIter != collider.info.gameObjects.end(); ++vecIter) {
		GameObject* go = *vecIter;
		if (go->tag == "Player" && go->HasComponent<HealthComponent>() && go->GetComponent<HealthComponent>().IsAlive()) {
			go->GetComponent<HealthComponent>().TakeDamage(damage);
			bullet->Destroy();
		}
	}
}