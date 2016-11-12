#include "BackgroundScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"

void BackgroundScript::Update(double deltaTime) {
	if (gameObject == nullptr || !gameObject->HasComponent<MeshRenderer>()) {
		return;
	}
	if (gameObject->GetComponent<MeshRenderer>().mesh == nullptr) {
		return;
	}
	gameObject->GetComponent<MeshRenderer>().mesh->textureOffset[1] += static_cast<float>(deltaTime) * scrollSpeed;
	while (gameObject->GetComponent<MeshRenderer>().mesh->textureOffset[1] > 1.0f) {
		gameObject->GetComponent<MeshRenderer>().mesh->textureOffset[1] -= 1.0f;
	}
}