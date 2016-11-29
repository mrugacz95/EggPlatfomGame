#include "MyWorld.h"
const float MyWorld::gravity = -9.81f;
MyWorld::MyWorld()
{
	world = new b2World(b2Vec2(0,gravity));
	std::cout << "World initialized\n";
}
b2World* MyWorld::get2bWorld(){
	return world;
}
MyWorld::~MyWorld()
{
	delete world;
}