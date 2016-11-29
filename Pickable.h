#pragma once
#include "Rectangle.h"
#include "TextureObject.h"
class Pickable : public TextureObject
{
public:
	Pickable(b2Vec2 position, std::string texName, b2World* world);
	Pickable(b2Vec2 position, ALLEGRO_BITMAP* bitmap, b2World* world);
	GameObject::GO_TYPES getType();
	std::string Pickable::serialize() override;
private:
	b2Vec2 pos;
};
