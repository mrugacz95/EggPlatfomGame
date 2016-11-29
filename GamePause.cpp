#include "GamePause.h"
void GamePause::init(){

	labels.push_back("Resume");
	labels.push_back("Main Menu");
}
GameState::GAME_STATE getType(){
	return GameState::GAME_PAUSE;
}
void GamePause::handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event){
	if (Event->type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (Event->keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			current--;
			if (current<0) current = labels.size() - 1;
			break;
		case ALLEGRO_KEY_DOWN:
			current++;
			if (current >= labels.size()) current = 0;
			break;
		case ALLEGRO_KEY_ESCAPE:
			sm->popGameState();
			break;
		case ALLEGRO_KEY_ENTER:
			switch (current)
			{
			case 0:
				sm->popGameState();
				return;
			case 1:
				sm->toMenu();
				return;
			default:
				sm->stop();
				break;
			}
			break;
		}
	}


}

void GamePause::draw(){
	for (int i = 0; i < labels.size(); i++){
		al_draw_text(FontManager::getFont("stdFont"), ((current == i) ? al_map_rgb(240, 240, 0) : al_map_rgb(255, 255, 255)), Camera::getScreenWidth() / 2, 50 + i * 40, ALLEGRO_ALIGN_CENTER, labels[i].c_str());
	}
}
GameState::GAME_STATE GamePause::getType(){
	return GAME_PAUSE;
}