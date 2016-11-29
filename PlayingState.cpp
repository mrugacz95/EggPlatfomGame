#include "PlayingState.h"

PlayingState::PlayingState(std::string levelPath){
	this->levelPath = levelPath;

}
void PlayingState::init(){
	keys.resize((int)LAST, false);
	modelManager = new ModelManager();
	modelManager->load(levelPath.c_str());
	contactListener = new MyContactListener(this,modelManager);
	modelManager->getWorld()->SetContactListener(contactListener);

	player = static_cast<Player*>(modelManager->getGameObject("player"));
	if (player == NULL){
		player = new Player(b2Vec2(0, 0), modelManager->getWorld());
	}
}
void PlayingState::draw(){
	modelManager->drawAll();
	al_draw_text(FontManager::getFont("stdFont"), al_map_rgb(255, 255, 255), Camera::getScreenWidth() - 20, 20, ALLEGRO_ALIGN_RIGHT, to_string(points).c_str());
	if(points>10)al_draw_text(FontManager::getFont("stdFont"), al_map_rgb(255, 255, 255), Camera::getScreenWidth() / 2, 50, ALLEGRO_ALIGN_CENTER, "Level complete!");

}
void PlayingState::cleanUp(){
	delete(modelManager);
	delete(contactListener);
}
void PlayingState::handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event){
	if (Event->type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (Event->keyboard.keycode)
		{
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = true;
			break;
		case ALLEGRO_KEY_UP:
			player->jump();
			break;
		case ALLEGRO_KEY_DOWN:
			break;
		case ALLEGRO_KEY_W:
			keys[W] = true;
			break;
		case ALLEGRO_KEY_S:
			keys[S] = true;
			break;
		case ALLEGRO_KEY_D:
			keys[D] = true;
			break;
		case ALLEGRO_KEY_A:
			keys[A] = true;
			break;
		case ALLEGRO_KEY_Q:
			Camera::zoomIn(2.f);
			break;
		case ALLEGRO_KEY_E:
			Camera::zoomOut(2.f);
			break;
		case ALLEGRO_KEY_ESCAPE:
			sm->pushGameState(new GamePause());
			break;

		default:
			break;
		}

	}
	else if (Event->type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (Event->keyboard.keycode)
		{
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = false;
			break;
		case ALLEGRO_KEY_UP:
			keys[UP] = false;
			break;
		case ALLEGRO_KEY_DOWN:
			break;
		case ALLEGRO_KEY_W:
			keys[W] = false;
			break;
		case ALLEGRO_KEY_S:
			keys[S] = false;
			break;
		case ALLEGRO_KEY_A:
			keys[A] = false;
			break;
		case ALLEGRO_KEY_D:
			keys[D] = false;
			break;

		default:
			break;
		}
	}
	if (!keys[LEFT] || !keys[RIGHT])
	if (keys[LEFT])
		player->moveLeft();
	else if (keys[RIGHT])
		player->moveRight();
	for (int i = 4; i < keys.size(); i++){
		if (keys[i])
			switch (i){
			case W:
				Camera::moveCamera(0, -5);
				break;
			case S:
				Camera::moveCamera(0, 5);
				break;
			case A:
				Camera::moveCamera(5, 0);
				break;
			case D:
				Camera::moveCamera(-5, 0);
				break;

		}
	}

	Camera::setCameraPos(player->getPos());
}
GameState::GAME_STATE PlayingState::getType(){
	return GAME;
}
void PlayingState::update(){
	modelManager->getWorld()->Step(timeStep, velocityIterations, positionIterations);
	modelManager->deleteDeadObjects();
}
void PlayingState::addPoints(int points){
	this->points += points;
}