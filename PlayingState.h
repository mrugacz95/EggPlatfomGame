#pragma once
#include <string>
#include "GamePause.h"
#include "GameState.h"
#include "FontManager.h"
#include "MyContactListener.h"
class PlayingState : public GameState
{
public:
	PlayingState(std::string levelPath);
	void init() override;
	void cleanUp() override;
	void draw() override;
	void handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event) override;
	GameState::GAME_STATE getType() override;
	PlayingState();
	void addPoints(int points);
	void update();
private:
	enum Keys{ UP, DOWN, LEFT, RIGHT, W, S, A, D, LAST };
	ModelManager *modelManager;
	std::string levelPath;
	std::vector<bool> keys;
	Player *player = NULL;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	float32 timeStep = 1.0f / 120.0f;
	MyContactListener *contactListener;
	int points = 0;
};
