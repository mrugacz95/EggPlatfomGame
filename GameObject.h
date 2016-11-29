#pragma once
#include <iostream>
#include <string>
#include <Box2D/Box2D.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include <fstream>
using namespace rapidjson;
class GameObject
{
public:
	virtual void draw() = 0;
	b2Body* getb2Body();
	b2Vec2 getPos();
	void setName(std::string name);
	std::string getName();
	enum GO_TYPES{CIRCLE,RECTANGLE,PLAYER,TEXT,PICKABLE,SENSOR,TEXTURE};
	virtual GO_TYPES getType() = 0;
	virtual std::string serialize() = 0;
private:
	std::string name;
protected:

	b2Body* body;
};
