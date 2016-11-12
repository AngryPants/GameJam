#include "E_CookieMaster.h"
#include "HealthComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameData.h"
#include "GameObjectFactory.h"

E_Cookie_Master::E_Cookie_Master() {
	lifeTime = 20.0f;
	cookieMaster = nullptr;
	movementSpeed = 2.0f;
	initialised = false;
	fireRate = 0.5f;
	timeToShoot = 1.0f / fireRate;
}

E_Cookie_Master::~E_Cookie_Master() {
}

void E_Cookie_Master::Shoot() {
	for (unsigned int i = 0; i < 6; ++i) {
		GameObject* bullet = &GameObjectFactory::CreateSpinach(cookieMaster->GetSpace());
		bullet->GetComponent<Transform>().SetRotation(0, 0, i * 60.0f);
	}
}

void E_Cookie_Master::Update(double deltaTime) {

	if (cookieMaster == nullptr) {
		return;
	}
	if (cookieMaster->HasComponent<Transform>() == false) {
		cookieMaster->AddComponent<Transform>();
	}
	if (cookieMaster->HasComponent<HealthComponent>() == false) {
		cookieMaster->AddComponent<HealthComponent>();
	}
	if (initialised == false) {
		initialised = true;
		float boundaryX = (GameData::GetInstance().worldSizeX + cookieMaster->GetComponent<Transform>().GetScale().x) * 0.3f;
		float boundaryY = (GameData::GetInstance().worldSizeY + cookieMaster->GetComponent<Transform>().GetScale().y) * 0.5f;
		cookieMaster->GetComponent<Transform>().SetPosition(0, -GameData::GetInstance().worldSizeY, 0);
		cookieMaster->GetComponent<HealthComponent>().SetMaxHealth(1000);
		cookieMaster->GetComponent<HealthComponent>().SetHealth(1000);
	}
	lifeTime -= deltaTime;
	if (lifeTime > 0.0f) {
		if (cookieMaster->GetComponent<Transform>().GetPosition().y < 0) {
			cookieMaster->GetComponent<Transform>().Translate(0, deltaTime * movementSpeed, 0);
		}
		else {
			timeToShoot -= deltaTime;
			if (timeToShoot < 0.0f) {
				Shoot();
				timeToShoot = 1.0 / fireRate;
			}
		}
	}
	else {
		if (cookieMaster->GetComponent<Transform>().GetPosition().y > -GameData::GetInstance().worldSizeY * 0.5f) {
			cookieMaster->GetComponent<Transform>().Translate(0, -deltaTime * movementSpeed, 0);
		}
		else {
			cookieMaster->Destroy();
		}
	}

	if (cookieMaster->GetComponent<HealthComponent>().IsAlive() == false) {
		cookieMaster->Destroy();
	}

}