#include "TextureObject.h"

TextureObject::TextureObject(b2Vec2 pos, ALLEGRO_BITMAP *bitmap, bool isStickedToScreen, b2World* world){
	if (!isStickedToScreen){
		this->inWorldWidth = Camera::calculateLengthInWorld(al_get_bitmap_width(bitmap));
		this->inWorldHeight = Camera::calculateLengthInWorld(al_get_bitmap_height(bitmap));
		MyRectangle* rect = new MyRectangle(inWorldWidth, inWorldHeight, pos, world);
		this->body=rect->getb2Body();
	}

	this->pos = pos;
	this->bitmap = bitmap;
	this->isStickedToScreen = isStickedToScreen;
	this->world = world;
}


void TextureObject::draw(){
	if (isStickedToScreen){
		al_draw_bitmap(bitmap, pos.x, pos.y, 0);
	}
	else {
		b2Vec2 tmp;
		tmp.Set(pos.x - inWorldWidth / 2, pos.y + inWorldHeight / 2); // rysujemy od lewgo górnego narożnika
		Camera::calculatePointOnScreen(&tmp);
		al_draw_bitmap(bitmap, tmp.x, tmp.y, 0);
	}
}


GameObject::GO_TYPES TextureObject::getType(){
	return TEXTURE;
};

std::string TextureObject::serialize(){ 
	return "";// "\"bitmapa\":{\"pos\":[" + std::to_string(pos.x) + "," + std::to_string(pos.y) + "]}";
};
TextureObject::~TextureObject(){
	if (!isStickedToScreen)
		world->DestroyBody(getb2Body());
}