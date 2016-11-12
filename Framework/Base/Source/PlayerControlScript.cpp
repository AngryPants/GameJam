#include "PlayerControlScript.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Transform.h"
#include "InputManager.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "GameData.h"
#include "AudioManager.h"

//Constructor(s) & Destructor
PlayerControlScript::PlayerControlScript() {
	player = nullptr;
	movementSpeed = 5.0f;
	fireRate = 6.0;
	timeToFire = 0.0;
	currentForm = PLAYER_FORM::FORM_DEFAULT;

	unlockForms[0] = true;
	for (unsigned int i = 1; i < NUM_FORM; ++i) {
		//unlockForms[i] = false;
		unlockForms[i] = true;
	}
}

PlayerControlScript::~PlayerControlScript() {
}

void PlayerControlScript::ShootKicKac() {
	GameObject& bullet = GameObjectFactory::CreateKicKac(player->GetSpace());
	bullet.GetComponent<Transform>().SetPosition(player->GetComponent<Transform>().GetPosition());
}

void PlayerControlScript::ShootBanana() {
	GameObject& bullet = GameObjectFactory::CreateBanana(player->GetSpace());
	bullet.GetComponent<Transform>().SetPosition(player->GetComponent<Transform>().GetPosition());
}

void PlayerControlScript::ShootCookie() {
	{
	GameObject& bullet = GameObjectFactory::CreateCookie(player->GetSpace());
	bullet.GetComponent<Transform>().SetPosition(player->GetComponent<Transform>().GetPosition());
	}

	{
		GameObject& bullet = GameObjectFactory::CreateCookie(player->GetSpace());
		bullet.GetComponent<Transform>().SetPosition(player->GetComponent<Transform>().GetPosition());
		bullet.GetComponent<Transform>().SetRotation(0, 0, 10);
	}

	{
		GameObject& bullet = GameObjectFactory::CreateCookie(player->GetSpace());
		bullet.GetComponent<Transform>().SetPosition(player->GetComponent<Transform>().GetPosition());
		bullet.GetComponent<Transform>().SetRotation(0, 0, -10);
	}
}

void PlayerControlScript::ShootMeatball() {
	GameObject& bullet = GameObjectFactory::CreateMeatball(player->GetSpace());
	bullet.GetComponent<Transform>().SetPosition(player->GetComponent<Transform>().GetPosition());
}

void PlayerControlScript::Update(double deltaTime) {
	if (player == nullptr) {
		return;
	}
	if (player->HasComponent<Transform>() == false) {
		player->AddComponent<Transform>();
	}

	//Movement
	Transform& playerTransform = player->GetComponent<Transform>();
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_LEFT]) {
		player->GetComponent<Transform>().Translate(-movementSpeed * static_cast<float>(deltaTime));
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_RIGHT]) {
		player->GetComponent<Transform>().Translate(movementSpeed * static_cast<float>(deltaTime));
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_FORWARD]) {
		player->GetComponent<Transform>().Translate(0, movementSpeed * static_cast<float>(deltaTime), 0);
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_BACKWARD]) {
		player->GetComponent<Transform>().Translate(0, -movementSpeed * static_cast<float>(deltaTime), 0);
	}

	//Bounds Checking
	float boundaryX = (GameData::GetInstance().worldSizeX - player->GetComponent<Transform>().GetScale().x) * 0.5f;
	float boundaryY = (GameData::GetInstance().worldSizeY - player->GetComponent<Transform>().GetScale().y) * 0.5f;
	if (playerTransform.GetPosition().x < -boundaryX) {
		playerTransform.SetPosition(-boundaryX, playerTransform.GetPosition().y, playerTransform.GetPosition().z);
	} else if (playerTransform.GetPosition().x > boundaryX) {
		playerTransform.SetPosition(boundaryX, playerTransform.GetPosition().y, playerTransform.GetPosition().z);
	}

	if (playerTransform.GetPosition().y > boundaryY * 0.8f) {
		playerTransform.SetPosition(playerTransform.GetPosition().x, boundaryY * 0.8f, playerTransform.GetPosition().z);
	} else if (playerTransform.GetPosition().y < -boundaryY * 0.8f) {
		playerTransform.SetPosition(playerTransform.GetPosition().x, -boundaryY * 0.8f, playerTransform.GetPosition().z);
	}

	//Form Switching
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT_DEFAULT]) {
		currentForm = FORM_DEFAULT;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT_OCTOMAN] && unlockForms[FORM_OCTOMAN]) {
		currentForm = FORM_OCTOMAN;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT_DONKEY_KING] && unlockForms[FORM_DONKEY_KING]) {
		currentForm = FORM_DONKEY_KING;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT_COOKIE_MASTER] && unlockForms[FORM_COOKIE_MASTER]) {
		currentForm = FORM_COOKIE_MASTER;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT_BOWSIR] && unlockForms[FORM_BOWSIR]) {
		currentForm = FORM_BOWSIR;
	}

	//Shooting
	timeToFire = Math::Max(0.0, timeToFire - deltaTime);
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOOT] && timeToFire <= 0.0) {
		AudioManager::GetInstance().PlayAudio2D("Audio//Music//shoot.wav", false);
		switch (currentForm) {
			case PLAYER_FORM::FORM_DEFAULT:
				ShootKicKac();
				fireRate = 3.0f;
				break;
			case PLAYER_FORM::FORM_OCTOMAN:
				ShootKicKac();
				fireRate = 3.0f;
				break;
			case PLAYER_FORM::FORM_DONKEY_KING:
				ShootBanana();
				fireRate = 2.0f;
				break;
			case PLAYER_FORM::FORM_COOKIE_MASTER:
				ShootCookie();
				fireRate = 1.5;
				break;
			case PLAYER_FORM::FORM_BOWSIR:
				ShootMeatball();
				fireRate = 7.0f;
				break;
		}		
		timeToFire = 1.0 / fireRate;
	}

}