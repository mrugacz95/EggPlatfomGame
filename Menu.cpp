#include "Menu.h"
#include "ChooseLevel.h"
#include "Authors.h"
void Menu::handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event){
		if (Event->type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (Event->keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				current--;
				if (current<0) current = menuLabels.size()-1;
				break;
			case ALLEGRO_KEY_DOWN:
				current++;
				if (current >= menuLabels.size()) current = 0;
				break;
			case ALLEGRO_KEY_ESCAPE:
				sm->stop();
				break;
			case ALLEGRO_KEY_ENTER:
				switch (current)
				{
				case 0:
					sm->pushGameState(new ChooseLevel());
					break;
				case 1:
					sm->pushGameState(new LevelEditor());
					break;
				case 2:














					sm->pushGameState(new Authors());
					break;
				case 3:
					break;
				default:
					sm->popGameState();
					break;
				}
				break;
			}
		}
	

}
void Menu::init(){
	menuLabels.push_back("NEW GAME");
	menuLabels.push_back("LEVEL EDITOR");
	menuLabels.push_back("AUTHORS");
	menuLabels.push_back("OPTIONS");
	menuLabels.push_back("EXIT");
}
void Menu::draw(){
	for (int i = 0; i < menuLabels.size();i++){
		al_draw_text(FontManager::getFont("stdFont"),((current==i)? al_map_rgb(240,240,0):al_map_rgb(255,255,255)), Camera::getScreenWidth()/2, 50+i*40, ALLEGRO_ALIGN_CENTER, menuLabels[i].c_str());
	}
}
GameState::GAME_STATE Menu::getType(){
	return GameState::MENU;

}