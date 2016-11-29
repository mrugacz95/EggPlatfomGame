#pragma once
#include "MyWorld.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "GameObject.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson/document.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Player.h"
#include "Text.h"
#include "Pickable.h"
#include "FontManager.h"
#include "TextureObject.h"
using namespace rapidjson;
//https://github.com/in2gpu/in2gpu_tutorials/blob/1e1ca75ff76a5813ea4686b160e7e9ad7ba83b90/in2gpu_tutorials/Chapter_2/BasicEngine/Managers/Models_Manager.cpp
class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	std::string addGameObject(std::string name, GameObject* gameObject);
	b2World* getWorld();
	void drawAll();
	void deleteAll();
	void delGameObject(GameObject* gameObject);
	void delGameObject(std::string name);
	void delGameObjectImmediately(std::string name);
	void load(std::string levelPath);
	void save(std::string path);
	void deleteDeadObjects();
	int countModels();
	GameObject* getGameObject(std::string name);
private:
	std::map <std::string, GameObject*> gameObjectsList;
	MyWorld world;
	enum STRING_TYPES{SIZE,POS,COLOR,DYNAMIC,RECT,CIRC,PLAYER,TEXT,PICKABLE,CIRCLE,FONT,PATH,STICKED_TO_SCREEN,COMMENT,UNDEF,TEXTURE};
	std::set<std::string> deadObjects; //nie vector ¿eby nazwy sie nie powtarza³y
	STRING_TYPES stringToEnum(std::string str);
	ALLEGRO_COLOR parseColor(Value::ConstMemberIterator colorIterator);
	b2Vec2 parsePosition(Value::ConstMemberIterator positionIterator);
};
