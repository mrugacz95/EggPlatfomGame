#pragma once
#include "ModelManager.h"
#include "Player.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <Box2D/Box2D.h>
#include <vector>
#include <stack>
#include "Camera.h"
#include "FontManager.h"

class GameState;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void start();
	void setModelManager(ModelManager* modelManager);
	void setPlayer(Player* player);
	void popGameState();
	void pushGameState(GameState* gs);
	void toMenu();
	void stop();
	void quit();
private:
	bool running = true;
	ModelManager* modelManager;
	float32 timeStep = 1.0f / 120.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	Player* player;
	ALLEGRO_EVENT Event;
	ALLEGRO_EVENT_QUEUE *EventQueue;
	ALLEGRO_DISPLAY *Screen;
	std::stack<GameState*> gameState;

};
