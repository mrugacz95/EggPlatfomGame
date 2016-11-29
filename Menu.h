#pragma once
#include <allegro5/allegro.h>
#include <vector>
#include <string>
#include <iostream>
#include "GameState.h"
#include "PlayingState.h"
#include "LevelEditor.h"
class Menu : public GameState
{
public:
	void draw() override;
	virtual void handleEvent(SceneManager *sm,ALLEGRO_EVENT *Event);
	void init() override;
	void cleanUp() override {};
	void update() override {};
	GameState::GAME_STATE getType() override;
protected:
	int current=0;
	std::vector<std::string> menuLabels;

};
