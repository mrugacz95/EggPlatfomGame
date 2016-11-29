#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_native_dialog.h>

class TextureManager
{
public:
	static bool load(std::string bitmapa, std::string filename);
	static ALLEGRO_BITMAP *getBitmap(std::string name);
	static void init();
	static void clean();
	static ALLEGRO_BITMAP* getPickableBitmap();

private:
	static std::map<std::string, ALLEGRO_BITMAP*> bitmapList;
	static std::vector<std::string> pickableBitmaps;
};