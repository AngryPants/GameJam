#include "SpriteRenderer.h"
#include "GameObject.h"

//Constructor(s) & Destructor
SpriteRenderer::SpriteRenderer(GameObject& gameObject) : Component("Sprite Renderer", gameObject) {
	mesh = nullptr;
	enableLight = false;
}

SpriteRenderer::~SpriteRenderer() {
}

//Interface
void SpriteRenderer::Update(double deltaTime) {
	if (mesh != nullptr) {
		mesh->Update(deltaTime);
	}
}