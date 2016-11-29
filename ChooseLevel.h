#pragma once
#include "GameState.h"
#include "Menu.h"
class ChooseLevel : public Menu
{
public:
	void init();
	void handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event);

};
