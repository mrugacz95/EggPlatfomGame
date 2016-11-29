#pragma once
#include "Circle.h"
#include "GameObject.h"
#include "Rectangle.h"
#include <math.h>
#include <set>
class Player : public GameObject
{
public:
	Player(b2Vec2 pos, b2World* world);
	~Player();
	void draw();
	void jump();
	void moveRight();
	void moveLeft();
	GameObject::GO_TYPES getType() override;
	void addContact(std::string name);
	std::string serialize() override;
	void subContact(std::string name);
	
	class Sensor :public GameObject{
	public:
		int getCollidersNum();
		void addCollider();
		void subCollider();
		void draw(){};
		std::string serialize() override;
		GameObject::GO_TYPES getType() override;
	private:
		int colidersNum=0;
	};
private:
	GameObject* middlePoint;
	static const int segments = 20;
	GameObject* points[segments*2];
	b2Joint* joints[segments * 8];
	static const float radius;
	static const float maxVelocity;
	b2World* world;
	std::set<std::string> contacts;
	void setColisionMask(b2Body* body);
	
	Sensor* sensor;
};
