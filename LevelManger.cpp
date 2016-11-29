#include "LevelManager.h"
LevelManager::LevelManager(std::string levelPath)
{
	this->levelPath = levelPath;
}

LevelManager::~LevelManager()
{
}

void LevelManager::save(){

}
void LevelManager::load(){
	std::fstream fstr;
	fstr.open(levelPath);
	std::string objectType,constructInfo;
	int i=0;
	while (fstr>>objectType)
	{
		std::cin >> constructInfo;
		switch (1)//objectType.c_str())
		{
		case 1://Rect":
			//modelManager.addGameObject(objectType, new MyRectangle(constructInfo));
		default:
			break;
		}
	}

}