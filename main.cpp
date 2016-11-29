/*
 * Marcin Mrugas Agata Kwiek
 *
 * PlatformGame 10/11 2015
 *
 */
#include <Box2D/Box2D.h>
#include "SceneManager.h"
#include "FontManager.h"
#include "Rectangle.h"
#include "Circle.h"
#include <cstdio>
#include <stdio.h>
#include "Player.h"
#include "Text.h"
#include "rapidjson/writer.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "MyContactListener.h"
#include "Pickable.h"
#include "TextureObject.h"
using namespace rapidjson;
int main(int argc, char** argv)
{

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	SceneManager sm;
	ModelManager* mm = new ModelManager();
	TextureManager *tm = new TextureManager();
	FontManager::init();
	TextureManager::init();
	sm.setModelManager(mm);
	//tm->load("bitmapa", "bitmaps/milk.png");
	//TextureObject *textura = new TextureObject(b2Vec2(100, 100), tm->getBitmap("bitmapa"), true);
	//mm->addGameObject("bitmapa", textura);
	//mm->setFontManager();
	//mm->load("Levels/lvl1.json");
	//sm.setPlayer(static_cast<Player*>(mm->getGameObject("Player")));
	//MyContactListener contactListener(mm);
	//mm->getWorld()->SetContactListener(&contactListener);
	sm.start();
	std::cout << "koniec\n";
	delete(mm);
	delete(tm);
	return 0;
}
