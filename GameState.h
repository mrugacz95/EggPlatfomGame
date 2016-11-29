#pragma once
#include <allegro5/allegro.h>
#include "SceneManager.h"
class GameState
{
public:
	virtual void init() = 0;
	virtual void cleanUp() = 0;

	virtual void update()=0;
	virtual void handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event) = 0;
	virtual void draw() = 0;
	enum GAME_STATE{MENU,GAME,OPTIONS,AUTHORS,LVL_EDITOR,GAME_PAUSE};
	virtual GAME_STATE getType()=0;

};