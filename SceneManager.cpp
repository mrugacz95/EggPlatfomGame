#include "SceneManager.h"
#include "GameState.h"
#include "Menu.h"
SceneManager::SceneManager()
{
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
	}
	//antylising

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
	al_init_native_dialog_addon();
	Screen = al_create_display(Camera::getScreenWidth(), Camera::getScreenHeight());
	if (al_get_display_option(Screen, ALLEGRO_SAMPLE_BUFFERS)) {
		printf("With multisampling, level %i\n",
			al_get_display_option(Screen, ALLEGRO_SAMPLES));
	}
	else {
		printf("Without multisampling.\n");
	}
	if (!Screen) {
		al_show_native_message_box(Screen, "Error!", "failed to create display!\n", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
	}
	EventQueue = al_create_event_queue();
	if (EventQueue == NULL)
	{
		al_show_native_message_box(Screen, "Error!", "Failed to create the event queue.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
	}

	if (!al_install_keyboard()) ///setup the keyboard
	{
		al_show_native_message_box(NULL, "Error!", "Failed to install keyboard.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
	}

	al_register_event_source(EventQueue, al_get_display_event_source(Screen));
	al_register_event_source(EventQueue, al_get_keyboard_event_source());

	if (!al_install_mouse()) {
		cout << "Error installing mouse.\n";
		quit();
	}
	al_register_event_source(EventQueue, al_get_mouse_event_source());
	al_init_primitives_addon();
	al_init_font_addon(); 
	al_init_image_addon();
	al_init_ttf_addon();
	std::cout << "Created SceneManager\n";
	gameState.push((GameState*)new Menu());

}
void SceneManager::setModelManager(ModelManager* modelManager){
	this->modelManager = modelManager;
}
void SceneManager::setPlayer(Player* player){
	this->player = player;
}


SceneManager::~SceneManager()
{
	al_destroy_display(Screen);
}
void SceneManager::pushGameState(GameState* gs){
	gameState.push(gs);
	gameState.top()->init();
}
void SceneManager::popGameState(){
	if (gameState.size() == 1){
		stop();
		return;
	}

	gameState.top()->cleanUp();
	gameState.pop();
}
void SceneManager::stop(){
	running = false;
}

void SceneManager::quit(){
	while (!gameState.empty()){
		gameState.top()->cleanUp();
		gameState.pop();
	}
}
//http://gamedevgeek.com/tutorials/managing-game-states-in-c/
void SceneManager::start(){
	if (gameState.empty())
		return;

	ALLEGRO_TIMEOUT timeout;
	gameState.top()->init();
	while (running)
	{
		al_clear_to_color(al_map_rgb(25, 55, 125));
		al_init_timeout(&timeout, timeStep);
		al_wait_for_event_until(EventQueue, &Event, &timeout);
		gameState.top()->handleEvent(this,&Event);
		gameState.top()->update();

		gameState.top()->draw();
		al_flip_display();
		
	}
	quit();
}
void SceneManager::toMenu(){
	do{
		popGameState();
	} while (gameState.top()->getType() != GameState::MENU);
}