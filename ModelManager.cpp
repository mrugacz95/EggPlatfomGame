#include "ModelManager.h"
ModelManager::ModelManager()
{
	std::cout << "Created ModelManager\n";
}
std::string ModelManager::addGameObject(std::string name, GameObject* gameobject){
	std::cout << "insert " << name << "\n"; 
	if (gameObjectsList.find(name) == gameObjectsList.end()){
		gameObjectsList.insert(std::pair<std::string, GameObject*>(name, gameobject));
		gameobject->setName(name);
		std::cout << "inserted " << name << "\n";
		return name;
	}
	else{
		cout << "Warrning: Dodawanie obiektu o tej samej nazwie.\n";
		name += to_string(countModels());
		if (gameObjectsList.find(name) == gameObjectsList.end()){
			gameObjectsList.insert(std::pair<std::string, GameObject*>(name, gameobject));
			gameobject->setName(name);
			std::cout << "inserted " << name << "\n";
			return name;
		}
		else{
			std::cout << "Error, powielone nazwy obiektow!";
			getWorld()->DestroyBody(gameobject->getb2Body());
			delete(gameobject);
		}
	}
	return "";
}
b2World* ModelManager::getWorld(){
	return world.get2bWorld();
}
void ModelManager::drawAll(){
	for (auto object : gameObjectsList)
		object.second->draw();
	
}
ModelManager::~ModelManager()
{
	deleteAll();
}
void ModelManager::deleteAll(){
	for (auto model : gameObjectsList)
	{
		delete model.second;
	}
	gameObjectsList.clear();
}
ModelManager::STRING_TYPES ModelManager::stringToEnum(std::string str){
	if (str == "size") return SIZE;
	if (str == "color") return COLOR;
	if (str == "pos") return POS;
	if (str == "dynamic") return DYNAMIC;
	if (str == "rect") return RECT;
	if (str == "circ") return CIRC;
	if (str == "circle") return CIRC;
	if (str == "player") return PLAYER;
	if (str == "Player") return PLAYER;
	if (str == "text") return TEXT;
	if (str == "pickable") return PICKABLE;
	if (str == "_comment") return COMMENT;
	if (str == "font") return FONT;
	if (str == "path") return PATH;
	if (str == "stickedToScreen") return STICKED_TO_SCREEN;
	return UNDEF;
}
void ModelManager::load(std::string levelPath){
	char readBuffer[65536];
	FILE* fp = fopen(levelPath.c_str(), "rb"); // non-Windows use "r"
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document document;
	document.ParseStream(is);
	fclose(fp);
	std::string name;
	int objectsNum=0; //TODO count Objects
	for (Value::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr){
		name = itr->name.GetString();
		switch (stringToEnum(name))
		{
			case RECT:
			{				//TODO Defultowe wartoœci
						 std::cout << "Rectangle [";
						 float32 width, height;
						 b2Vec2 pos;
						 bool dynamic = false;
						 ALLEGRO_COLOR color;
						 Value::ConstValueIterator itr3;
						 for (Value::ConstMemberIterator itr2 = itr->value.MemberBegin(); itr2 != itr->value.MemberEnd(); ++itr2)
							 switch (stringToEnum(itr2->name.GetString()))
						 {
							 case SIZE:
							 {
										  itr3 = itr2->value.Begin();
										  width = itr3->GetDouble();
										  itr3++;
										  height = itr3->GetDouble();
										  std::cout << "size[" << width << "," << height << "], ";
							 }
								 break;
							 case POS:
								 pos = parsePosition(itr2);
								 break;
							 case COLOR:
								 color = parseColor(itr2);
								 break;
							 case DYNAMIC:
								 dynamic = itr2->value.GetBool();
								 std::cout << "dynamic:" << ((dynamic) ? "true" : "false");
								 break;
							 case COMMENT: break;
							 default:
								 std::cout << ">Nie rozpoznano parametru: " << itr2->name.GetString() << "\n";
								 break;
						 }
						 std::cout << "]\n";
						 MyRectangle *rect = new MyRectangle(width, height, color, pos, getWorld(), dynamic);
						 std::string objName = "rect";
						 name.push_back('0' + objectsNum++);
						 addGameObject(name, rect);
			}
				break;
			case CIRC:
			{
						 std::cout << "Circle [";
						 double radius;
						 b2Vec2 pos;
						 bool dynamic = false;
						 ALLEGRO_COLOR color;
						 for (Value::ConstMemberIterator itr2 = itr->value.MemberBegin(); itr2 != itr->value.MemberEnd(); ++itr2)
							 switch (stringToEnum(itr2->name.GetString())){
							 case SIZE:
								 radius = itr2->value.GetDouble();
								 break;
							 case POS:
								 pos = parsePosition(itr2);
								 break;
							 case COLOR:
								 color = parseColor(itr2);
								 break;
							 case DYNAMIC:
								 dynamic = itr2->value.GetBool();
								 std::cout << "dynamic:" << ((dynamic) ? "true" : "false");
								 break;
							 case COMMENT: break;
							 default:
								 std::cout << ">Nie rozpoznano parametru: " << itr2->name.GetString() << "\n";
								 break;
						 }

						 std::cout << "]\n";
						 MyCircle *circ = new MyCircle(radius, color, pos, getWorld(), dynamic);
						 std::string objName = "circ";
						 name.push_back('0' + objectsNum++);
						 addGameObject(name, circ);
			}
				break;
			case PLAYER:
			{
				b2Vec2 pos;
				int width, height;
				ALLEGRO_COLOR color;
				float radius;
				for (Value::ConstMemberIterator itr2 = itr->value.MemberBegin(); itr2 != itr->value.MemberEnd(); ++itr2)
					switch (stringToEnum(itr2->name.GetString())){
					case SIZE:
						radius = itr2->value.GetDouble();
						break;
					case POS:
						pos = parsePosition(itr2);
						break;
					case COLOR:
						color = parseColor(itr2);
						break;
					case COMMENT: break;
					default:
						std::cout << ">Nie rozpoznano parametru" << itr2->name.GetString() << "\n";
						break;
				}
				Player* player = new Player(pos, getWorld());
				addGameObject("player", player);
			}
				break;
			case TEXT:
			{

						 ALLEGRO_COLOR color;
						 b2Vec2 pos;
						 std::string str,font,path;
						 bool stickedToScreen;
						 int size=32;
					for (Value::ConstMemberIterator itr2 = itr->value.MemberBegin(); itr2 != itr->value.MemberEnd(); ++itr2)
						switch (stringToEnum(itr2->name.GetString())){
						case TEXT:
							str = itr2->value.GetString();
							break;					
						case SIZE:
								size = itr2->value.GetInt();
								break;
						case POS:
							pos = parsePosition(itr2);
							break;
						case COLOR:
							color = parseColor(itr2);
							break;
						case PATH:
							path = itr2->value.GetString();
							break;
						case FONT://TODO not used
							font = itr2->value.GetString();
							break;
						case STICKED_TO_SCREEN:
							stickedToScreen = itr2->value.GetBool();
						case COMMENT: break;
						default:
							std::cout << ">Nie rozpoznano parametru" << itr2->name.GetString() << "\n";

							break;
					}
					std::string objName = "tex";
					name.push_back('0' + objectsNum++);
					if (!path.empty()){
						std::string fontName;
						fontName="font";
						fontName.push_back(size+'0');
						FontManager::loadFont(fontName, path, size);
						Text *tex = new Text(pos, color, str, FontManager::getFont(fontName), stickedToScreen);
						
						addGameObject(name, tex);
					}
					else{

						Text *tex = new Text(pos, color, str, FontManager::getFont("stdFont"), stickedToScreen);
						addGameObject(name, tex);
					}
			}
				break;
			case PICKABLE:
			{
							 std::cout << "Pickable [";
							 int width, height;
							 b2Vec2 pos;
							 bool dynamic = false;
							 ALLEGRO_COLOR color;
							 Value::ConstValueIterator itr3;
							 for (Value::ConstMemberIterator itr2 = itr->value.MemberBegin(); itr2 != itr->value.MemberEnd(); ++itr2)
								 switch (stringToEnum(itr2->name.GetString()))
							 {
								 case SIZE:
								 {
											  itr3 = itr2->value.Begin();
											  width = itr3->GetDouble();
											  itr3++;
											  height = itr3->GetDouble();
											  std::cout << "size[" << width << "," << height << "], ";
								 }
									 break;
								 case POS:
									 pos = parsePosition(itr2);
									 break;
								 case COLOR:
									 color = parseColor(itr2);
									 break;
								 case DYNAMIC:
									 dynamic = itr2->value.GetBool();
									 std::cout << "dynamic:" << ((dynamic) ? "true" : "false");
									 break;
								 case COMMENT: break;
								 default:
									 std::cout << ">Nie rozpoznano parametru: " << itr2->name.GetString() << "\n";
									 break;
							 }
							 std::cout << "]\n";
							 Pickable *pickable = new Pickable(pos,TextureManager::getPickableBitmap(), getWorld());
							 std::string objName = "pickable";
							 name += to_string(objectsNum++);
							 addGameObject(name, pickable);
			}
				break;
			default:
				std::cout << "Failed to load: " << name << "\n";
				break;
		}
	}
}
//Obiekty nie mog¹ byæ usuwanie w trakcie wykonywania step'u
void ModelManager::delGameObject(GameObject* gameObject){
	deadObjects.insert(gameObject->getName());
}
void ModelManager::delGameObject(std::string name){
	deadObjects.insert(name);
}
void ModelManager::delGameObjectImmediately(std::string name){
	if (gameObjectsList.find(name) == gameObjectsList.end()) return;
	getWorld()->DestroyBody(gameObjectsList.find(name)->second->getb2Body());
	delete(gameObjectsList.find(name)->second);
	gameObjectsList.erase(name);
}
void ModelManager::deleteDeadObjects(){
	if (deadObjects.size()>0)
		for (auto name : deadObjects){
			getWorld()->DestroyBody(gameObjectsList.find(name)->second->getb2Body());
			delete(gameObjectsList.find(name)->second);
			gameObjectsList.erase(name);
		}
	deadObjects.clear();
}
ALLEGRO_COLOR ModelManager::parseColor(Value::ConstMemberIterator colorIterator){

	Value::ConstValueIterator itr;
	itr = colorIterator->value.Begin();
	int r, g, b;
	r = itr->GetInt();
	g = (++itr)->GetInt();
	b = (++itr)->GetInt();
	std::cout << "color [" << r << "," << g << "," << b << "], ";
	return al_map_rgb(r,g,b);
}
b2Vec2 ModelManager::parsePosition(Value::ConstMemberIterator positionIterator){
	b2Vec2 pos;
	Value::ConstValueIterator itr;
	itr = positionIterator->value.Begin();
	pos.Set(itr->GetDouble(), 0);
	pos.Set(pos.x, (++itr)->GetDouble());
	std::cout << "pos[" << pos.x << "," << pos.y << "], ";
	return pos;
}
GameObject* ModelManager::getGameObject(std::string name){
	std::map<std::string,GameObject*>::iterator toRet = gameObjectsList.find(name);
	if (toRet != gameObjectsList.end())
		return toRet->second;
	std::cout << "Couldnt find game object: " << name<<"\n";
	return NULL;
}
void ModelManager::save(std::string path){
	std::fstream out;
	out.open(path, std::fstream::trunc | std::fstream::out);
	if (!out.good()){
		std::cout << "Culdn't open file: " << path << "\n";
		return;
	}
	cout << "Successuly opened file\n";
	out << "{";
	for (std::map<std::string, GameObject*>::iterator it = gameObjectsList.begin();;){
		out<<"\t"<<it->second->serialize();
		if (++it!=gameObjectsList.end()) out << ",";
		else break;
		out << "\n";
	}
	out << "\n}";
	out.close();
	cout << "Successuly saved file\n";
}
int ModelManager::countModels(){
	return gameObjectsList.size();
}