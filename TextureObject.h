#pragma once
#include "Rectangle.h"
#include "Camera.h"
#include "TextureManager.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_native_dialog.h>

class TextureObject : public GameObject
{
public:
	TextureObject(b2Vec2 pos, ALLEGRO_BITMAP *bitmap, bool isStickedToScreen, b2World* world);
	void draw()override;
	GameObject::GO_TYPES getType();
	std::string serialize() override;
	~TextureObject();
	
private:
	b2Vec2 pos;
	ALLEGRO_BITMAP *bitmap;
	bool isStickedToScreen;
	b2World* world;
	float32 inWorldWidth,
		inWorldHeight;
};
