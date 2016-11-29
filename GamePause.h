#pragma once
#include "GameState.h"
#include "FontManager.h"

class GamePause : public GameState
{
public:
	void init() override;
	GameState::GAME_STATE getType() override;
	void handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event) override;
	void cleanUp() override {};
	void update() override {};
	void draw() override;
private:
	std::vector<std::string> labels;
	FontManager *fontManager;
	int current = 0;
};