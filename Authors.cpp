#include"Authors.h"
void Authors::draw(){
	al_draw_text(FontManager::getFont("stdFont"), al_map_rgb(240, 240, 0), Camera::getScreenWidth()/2-120, Camera::getScreenHeight()/2-100, ALLEGRO_ALIGN_LEFT,"Authors:");
	al_draw_text(FontManager::getFont("stdFont"), al_map_rgb(255, 255, 255), Camera::getScreenWidth() / 2-70, Camera::getScreenHeight() / 2 - 50, ALLEGRO_ALIGN_LEFT, "Agata Kwiek");
	al_draw_text(FontManager::getFont("stdFont"), al_map_rgb(255, 255, 255), Camera::getScreenWidth() / 2-70, Camera::getScreenHeight() / 2 , ALLEGRO_ALIGN_LEFT, "Marcin Mrugas");
};

void Authors::handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event){
	if (Event->keyboard.type == ALLEGRO_EVENT_KEY_DOWN)
		switch (Event->keyboard.keycode)
		{
		case ALLEGRO_KEY_ENTER:
		case ALLEGRO_KEY_ESCAPE:
			sm->popGameState();
			break;

		default:
			break;
		}

};

GameState::GAME_STATE Authors::getType(){
	return GameState::AUTHORS;
};