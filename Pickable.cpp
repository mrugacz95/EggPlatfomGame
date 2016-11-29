#include "Pickable.h"
Pickable::Pickable(b2Vec2 position, ALLEGRO_BITMAP *bitmap, b2World* world) :
TextureObject(position, bitmap, false, world){
	body->SetUserData(this);
	this->pos = position;
	b2Filter filter;
	filter.maskBits = 6; //0000010b
	filter.categoryBits = 2; //0000010b
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		f->SetFilterData(filter);
	}
}
Pickable::Pickable(b2Vec2 pos, std::string texName, b2World* world) : Pickable::Pickable(pos, TextureManager::getBitmap(texName), world){};
GameObject::GO_TYPES Pickable::getType(){
	return PICKABLE;
}

std::string Pickable::serialize(){ return "\"pickable\":{\"pos\":[" + std::to_string(pos.x) + ","+std::to_string(pos.y)+"]}"; }