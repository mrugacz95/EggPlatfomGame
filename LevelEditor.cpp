#include "LevelEditor.h"
const std::string LevelEditor::lvlEditorFont = "lvlEditorFont";
void LevelEditor::handleEvent(SceneManager *sm, ALLEGRO_EVENT *Event){
	
	//Start Region Keys down
	if (Event->type == ALLEGRO_EVENT_KEY_DOWN)
	{
		keys[Event->keyboard.keycode] = true;
		switch (Event->keyboard.keycode)
		{
		case ALLEGRO_KEY_Q:
			Camera::zoomIn(2.f);
			break;
		case ALLEGRO_KEY_E:
			Camera::zoomOut(2.f);
			break;
		case ALLEGRO_KEY_ESCAPE:
			sm->pushGameState(new GamePause());
			break;
		case ALLEGRO_KEY_X:
			modelManager->save("Levels/current.json");
			break;
		case ALLEGRO_KEY_L:
			modelManager->deleteAll();
			modelManager->load("Levels/current.json");
			break;
		case ALLEGRO_KEY_P:
			currentGameObject = GameObject::PLAYER;
			break;
		case ALLEGRO_KEY_R:
			currentGameObject = GameObject::RECTANGLE;
			break;
		case ALLEGRO_KEY_C:
			currentGameObject = GameObject::CIRCLE;
			break;
		case ALLEGRO_KEY_T:
			currentGameObject = GameObject::TEXT;
			break;
		case ALLEGRO_KEY_G:
			currentGameObject = GameObject::PICKABLE;
			break;
		case ALLEGRO_KEY_M:
			currentDynamic = !currentDynamic;
			break;
		case ALLEGRO_KEY_Z:
			if (!lastNames.empty()){
				modelManager->delGameObjectImmediately(lastNames.top());
				lastNames.pop();
			}
			break;

		default:
			break;
		}

	}
	//End region keys up
	//start region keys up
	else if (Event->type == ALLEGRO_EVENT_KEY_UP)
	{
		keys[Event->keyboard.keycode] = false;
	}
	//End region keys up
	else if(Event->type != ALLEGRO_EVENT_TIMER)
		switch (Event->type)
		{
		case ALLEGRO_EVENT_MOUSE_AXES:
			mouseAxes(&Event->mouse);
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (mouseButtonUp){
				mouseButtonUp = false;
				mouseDown(&Event->mouse);
			}
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if (!mouseButtonUp){
				mouseButtonUp = true;
				mouseUp(&Event->mouse);
			}
			break;

		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
			break;

		case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
			break;
		default:
			break;
		}
	
	for (int i = 0; i < keys.size(); i++){
		if (keys[i])
			switch (i){
			case ALLEGRO_KEY_UP:
			case ALLEGRO_KEY_W:
				Camera::moveCamera(0, -5);
				break;
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_S:
				Camera::moveCamera(0, 5);
				break;
			case ALLEGRO_KEY_LEFT:
			case ALLEGRO_KEY_A:
				Camera::moveCamera(5, 0);
				break;
			case ALLEGRO_KEY_RIGHT:
			case ALLEGRO_KEY_D:
				Camera::moveCamera(-5, 0);
				break;

		}
	}
}
void LevelEditor::draw(){
	modelManager->drawAll();
	drawGUI();
}
void LevelEditor::init(){
	keys.resize(ALLEGRO_KEY_MAX, false);
	modelManager = new ModelManager();
	GUILabels.push_back("GameObjects: Rectangle(R) Player(P) Circle(C) Pickable(G) Text(T)");
	GUILabels.push_back("Other opstions: Save(X), Load(L) to current.json, Redo(Z)");
	GUILabels.push_back("Current GameObject:");
	GUILabels.push_back("Current dynamic:");
	srand(time(NULL));
}
void LevelEditor::cleanUp(){
	delete(modelManager);
}
void LevelEditor::update(){

}
void LevelEditor::drawGUI(){
	for (int i = 0; i < GUILabels.size();i++){
		if ((currentGameObject != GameObject::RECTANGLE && currentGameObject != GameObject::CIRCLE) && i == 3) continue;
		al_draw_text(FontManager::getFont(lvlEditorFont), al_map_rgb(230, 230, 230), 10, 10 + i * 15,0 ,GUILabels[i].c_str());

		switch (i)
		{
			case 2: // Jaki GameObject
			{
				std::string go;
				switch (currentGameObject)
				{
				case GameObject::PLAYER:
					go = "Player";
					break;
				case GameObject::RECTANGLE:
					go = "Rectangle";
					break;
				case GameObject::CIRCLE:
					go = "Circle";
					break;
				case GameObject::TEXT:
					go = "Text";
					break;
				case GameObject::PICKABLE:
					go = "Pickable";
					break;
				default:
					break;
				}
				al_draw_text(FontManager::getFont(lvlEditorFont), al_map_rgb(230, 230, 230), 190, 10 + i * 15, 0, go.c_str());
				break;
			}
			case 3:
				al_draw_text(FontManager::getFont(lvlEditorFont), al_map_rgb(230, 230, 230), 190, 10 + i * 15, 0, (currentDynamic)?"dynamic":"static");
				break;
		default:
			break;
		}
	}

}
GameState::GAME_STATE LevelEditor::getType(){
	return LVL_EDITOR;
}
void LevelEditor::mouseUp(ALLEGRO_MOUSE_EVENT *event){
	if (dMouse.x == 0 && dMouse.y == 0) return;
	b2Vec2 pos;
	pos = Camera::calculatePointInWorld(b2Vec2(event->x, event->y));
	switch (currentGameObject)
	{
	case GameObject::RECTANGLE:{
		b2Vec2 center;
		center.Set(mousePos.x + (dMouse.x / 2), mousePos.y + (dMouse.y / 2));
		dMouse.x *= (dMouse.x < 0)? - 1:1;
		dMouse.y *= (dMouse.y < 0)? - 1:1;
		lastNames.push(modelManager->addGameObject("rect", new MyRectangle(Camera::calculateLengthInWorld(dMouse.x), Camera::calculateLengthInWorld(dMouse.y), randColor, Camera::calculatePointInWorld(center), modelManager->getWorld(), currentDynamic)));
		break;
		}
	case GameObject::PLAYER:
		if (modelManager->getGameObject("player") != NULL) //Mo¿e byæ tylko jeden player
			modelManager->delGameObjectImmediately("player");
		lastNames.push(modelManager->addGameObject("player", new Player(pos, modelManager->getWorld())));
		break;
	case GameObject::PICKABLE:{
				modelManager->addGameObject("pickable", new Pickable(pos, TextureManager::getPickableBitmap(), modelManager->getWorld()));
				break;
		}
	case GameObject::CIRCLE:
		lastNames.push(modelManager->addGameObject("circle", new MyCircle(Camera::calculateLengthInWorld(dMouse.Length()), randColor, Camera::calculatePointInWorld(mousePos), modelManager->getWorld(), currentDynamic)));
		break;
	case GameObject::TEXT:{
		std::string text;
		cout << "Podaj tekst do TextObjectu\n";
		getline(std::cin,text);
		lastNames.push(modelManager->addGameObject("text", new Text(pos, al_map_rgb(240, 240, 240), text, FontManager::getFont("stdFont"), true)));
		break;
		}
	default:
		break;
	}
	dMouse.Set(0, 0);
}
void LevelEditor::mouseDown(ALLEGRO_MOUSE_EVENT *event){
	mousePos.Set(event->x, event->y);

	randColor = al_map_rgb(rand() % 256, rand() % 256, rand() % 256);
	
}

void LevelEditor::mouseAxes(ALLEGRO_MOUSE_EVENT *event){
	dMouse.Set(event->x - mousePos.x, event->y - mousePos.y);
	if (!mouseButtonUp){
		switch (currentGameObject)
		{
		case GameObject::RECTANGLE:
			al_draw_filled_triangle(mousePos.x, mousePos.y, event->x, event->y, mousePos.x, event->y, randColor);
			al_draw_filled_triangle(mousePos.x, mousePos.y, event->x, event->y, event->x, mousePos.y, randColor);

			break;
		case GameObject::PLAYER:
			al_draw_filled_circle(event->x, event->y, Camera::calculateLengthOnScreen(1.5), al_map_rgb(255, 255, 255));
			al_draw_filled_circle(event->x, event->y, Camera::calculateLengthOnScreen(0.5f), al_map_rgb(254, 170, 0));
			break;
		case GameObject::CIRCLE:
			al_draw_filled_circle(mousePos.x, mousePos.y, dMouse.Length(), randColor);
			break;
		case GameObject::TEXT:
			al_draw_text(FontManager::getFont("stdFont"),al_map_rgb(240,240,240),event->x,event->y,ALLEGRO_ALIGN_CENTER,"text");
			break;
		case GameObject::PICKABLE:{
			float size = Camera::calculateLengthOnScreen(1);
			al_draw_filled_rectangle(event->x - size, event->y - size, event->x + size, event->y + size, al_map_rgb(255, 255, 255)); //TODO dodaæ define COL_WHITE
		}
			break;
		default:
			break;
		}
		
	}

}