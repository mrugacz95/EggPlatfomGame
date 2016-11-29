#pragma once
#include "GamePause.h"
#include "GameState.h"
#include "Rectangle.h"
#include "ModelManager.h"
#include "Camera.h"
class LevelEditor : public GameState
{
public:
	void handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event) override;
	void cleanUp() override;
	void update() override;
	void draw() override;
	void init() override;
	GameState::GAME_STATE getType() override;
private:
	ModelManager *modelManager;
	void drawGUI();
	b2Vec2 mousePos;
	b2Vec2 dMouse;
	enum Keys{ UP, DOWN, LEFT, RIGHT, W, S, A, D,X,P, LAST };
	std::vector<bool> keys;
	void mouseDown(ALLEGRO_MOUSE_EVENT *event);
	void mouseUp(ALLEGRO_MOUSE_EVENT *event);
	void mouseAxes(ALLEGRO_MOUSE_EVENT *event);
	bool mouseButtonUp = true;
	GameObject::GO_TYPES currentGameObject=GameObject::RECTANGLE;
	ALLEGRO_COLOR randColor;
	std::vector<std::string> GUILabels;
	static const std::string lvlEditorFont;
	bool currentDynamic = false;
	std::stack<std::string> lastNames;
};
