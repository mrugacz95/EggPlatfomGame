#pragma once
#include "GameObject.h"
#include "Camera.h"
#include <fstream>
using namespace std;
class MyCircle : public GameObject
{
public:
	MyCircle(float radius, ALLEGRO_COLOR color, b2Vec2 position, b2World* world, bool dynamic);
	void draw();
	std::string serialize() override;
	GameObject::GO_TYPES getType() override;
private:
	float radius;
	bool dynamic;
	ALLEGRO_COLOR color;
};

