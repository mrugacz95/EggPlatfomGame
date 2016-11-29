#include "TextureManager.h"
std::map<std::string, ALLEGRO_BITMAP*> TextureManager::bitmapList; //inicjowanie statycznego elementu bitmaplist (membera klasy)
std::vector<std::string> TextureManager::pickableBitmaps;
bool TextureManager::load(std::string name, std::string filename){

	if (bitmapList.find(name) != bitmapList.end())
		return true;
	ALLEGRO_BITMAP *bitmap = al_load_bitmap(filename.c_str());
	if (!bitmap){
		std::cout<<"Could not load "+filename+".\n";
		return false;
	}
	std::cout << "Succesfully loaded " + filename + ".\n";
	bitmapList.insert(std::pair<std::string, ALLEGRO_BITMAP*>(name, bitmap));
	return true;
}

void TextureManager::clean()
{
	for (auto pair : bitmapList)
		al_destroy_bitmap(pair.second);
	bitmapList.clear();
}

void TextureManager::init(){
	pickableBitmaps.push_back("flour");
	pickableBitmaps.push_back("sugar");
	pickableBitmaps.push_back("milk");
	pickableBitmaps.push_back("salt");
	for (std::string name : pickableBitmaps)
		load(name, "bitmaps/"+name+".jpg");
	std::cout << "TextureManager initized";
}

ALLEGRO_BITMAP* TextureManager::getBitmap(std::string name){
	return (bitmapList.at(name));
}
ALLEGRO_BITMAP* TextureManager::getPickableBitmap(){
	int num = rand() % 3;
	std::string name=pickableBitmaps[num];
	if (bitmapList.find(name) != bitmapList.end())
		return bitmapList.find(name)->second;
	return NULL;
}
