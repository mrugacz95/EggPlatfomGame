#include "FontManager.h"
std::map<std::string, ALLEGRO_FONT*> FontManager::fontsList; //inicjowanie statycznego elementu fontlist //wtf

bool FontManager::loadFont(std::string name, std::string path,int size){
	std::cout << "Font:" << name << " " << path << " " << size << "\n";
	if (fontsList.find(name) != fontsList.end())
		return true;
	ALLEGRO_FONT *font = al_load_ttf_font(path.c_str(), size, 0);
	if (!font){
		std::cout<<"Could not load font "+path+" size:"<<size<<"\n";
		return false;
	}
	std::cout << "Succesfully loaded font "+path+".\n";
	fontsList.insert(std::pair<std::string,ALLEGRO_FONT*>(name, font));
	return true;
}

void FontManager::init(){
	loadFont("stdFont", "EightBaller.ttf", 35);
	loadFont("lvlEditorFont", "JackInput.ttf", 14);
	std::cout << "FontManager initized\n";
}
void FontManager::clean()
{
	for (auto pair : fontsList)
		al_destroy_font( pair.second);
	fontsList.clear();
}
ALLEGRO_FONT* FontManager::getFont(std::string name){
	if (fontsList.find(name)!=fontsList.end())
		return (fontsList.find(name)->second);
	std::cout << "Font /"""<<name<<"/"" not found\n";
	if (fontsList.size()>0)
	return fontsList.begin()->second;
	else return NULL;
}