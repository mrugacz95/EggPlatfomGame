#pragma once
#include <string>
#include <map>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class FontManager
{
public:
	static bool loadFont(std::string name, std::string path, int size);
	static ALLEGRO_FONT* getFont(std::string name);
	static void init();
	static void clean();

private:
	static std::map<std::string, ALLEGRO_FONT*> fontsList;
};
