#include "ChooseLevel.h"
void ChooseLevel::init(){
	menuLabels.push_back("LEVEL 1");
	menuLabels.push_back("LEVEL 2");
	menuLabels.push_back("LEVEL 3");
	menuLabels.push_back("CURRENT");
	menuLabels.push_back("BACK");
}
void ChooseLevel::handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event){
	if (Event->type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (Event->keyboard.keycode)
		{
		case ALLEGRO_KEY_UP:
			current--;
			if (current<0) current = menuLabels.size() - 1;
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
				sm->pushGameState(new PlayingState("Levels/lvl1.json"));
				break;
			case 1:
				sm->pushGameState(new PlayingState("Levels/lvl2.json"));
				break;
			case 2:
				sm->pushGameState(new PlayingState("Levels/lvl3.json"));
				break;
			case 3:
				sm->pushGameState(new PlayingState("Levels/current.json"));
				break;
			default:
				sm->popGameState();
				break;
			}
			break;
		}
	}


}