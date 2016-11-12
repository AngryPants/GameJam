#include "B_Banana_Script.h"
#include "GameObject.h"
#include "Transform.h"
#include "SphereCollider.h"
#include "HealthComponent.h"
#include "GameData.h"

void B_Banana_Script::Update(double deltaTime) {
	if (bullet == nullptr) {
		return;
	}
	if (bullet->HasComponent<Transform>() == false) {
		bullet->AddComponent<Transform>();
	}

	Transform& bulletTransform = bullet->GetComponent<Transform>();
	lifeTime -= deltaTime;
	positionOffset += static_cast<float>(deltaTime) * 5.0f;
	scaleIncrease += deltaTime * 0.3f;
	if (lifeTime > 0.0) {
		bulletTransform.Translate(0, speed * deltaTime, 0);
		bulletTransform.Translate(cos(positionOffset) * deltaTime * 5.0f, 0, 0);
		bulletTransform.Rotate(0, 0, deltaTime * 720.0f);
		bulletTransform.SetScale(Vector3(1 + scaleIncrease, 1 + scaleIncrease, 1));
		bullet->GetComponent<SphereCollider>().SetRadius(bulletTransform.GetScale().x * 0.15f);
	} else {
		bullet->Destroy();
	}

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

}