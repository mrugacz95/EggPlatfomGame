#pragma once
#include <iostream>
#include <Box2D/Box2D.h>
class MyWorld
{
public:
	MyWorld();
	~MyWorld();
	b2World* get2bWorld();

private:
	static const float gravity;
	b2World* world;
};