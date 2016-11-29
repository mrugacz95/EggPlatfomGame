#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Math.h"
class MyRectangle: public GameObject
{
public:
	MyRectangle(float32 width, float32 height, b2Vec2 position, b2World* world);
	MyRectangle(float32 width, float32 height, b2Vec2 position, b2World* world, bool dynamic);
	MyRectangle(float32 width, float32 height, ALLEGRO_COLOR color, b2Vec2 position, b2World* world);
	MyRectangle(float32 width, float32 height, ALLEGRO_COLOR color, b2Vec2 position, b2World* world, bool dynamic);
	void draw();
	void multip();
	std::string serialize() override;

	GameObject::GO_TYPES getType() override;
private:
	float32 width;
	float32 height;
	ALLEGRO_COLOR color;
	b2Vec2 pos;
	bool dynamic;
};
