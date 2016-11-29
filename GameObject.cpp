#include "GameObject.h"
#include "Camera.h"
#include "math.h"
b2Body* GameObject::getb2Body(){
	return body;
}
b2Vec2 GameObject::getPos(){
	return body->GetPosition();
}
void GameObject::setName(std::string name){
	this->name = name;
}
std::string GameObject::getName(){
	return name;
}
