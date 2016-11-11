#include "B_Cookie_Script.h"
#include "GameObject.h"

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
	} else {
		bullet->Destroy();
	}	

}