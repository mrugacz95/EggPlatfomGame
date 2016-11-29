#pragma once
#include "ModelManager.h"
#include "GameObject.h"
#include "Rectangle.h"
#include <fstream>
class LevelManager
{
public:
	LevelManager(std::string levelPath);
	~LevelManager();
	void save();
private:
	ModelManager modelManager;
	std::string levelPath;
	void load();
};
