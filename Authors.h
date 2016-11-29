#pragma once
#include "GameState.h"
class Authors : public GameState
{
public:
	void init()override{};
	void draw() override;
	void cleanUp() override {};
	void update() override {};
	void handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event) override;
	GameState::GAME_STATE getType() override;
private:

};
