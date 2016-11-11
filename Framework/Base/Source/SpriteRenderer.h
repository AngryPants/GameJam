#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Component.h"
#include "SpriteAnimation.h"
#include "Animation.h"
#include "TextureList.h"
#include <map>

using std::map;

class SpriteRenderer : public Component {
	
public:
	//Variable(s)
	SpriteAnimation* mesh;
	TextureList textureList;
	map<string, Animation> animations;	
	bool enableLight;

	//Constructor(s) & Destructor
	SpriteRenderer(GameObject& gameObject);
	virtual ~SpriteRenderer();

	//Interface
	void Update(double deltaTime);
	
};

#endif