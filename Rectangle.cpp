#include "Rectangle.h"

MyRectangle::MyRectangle(float32 width, float32 height, b2Vec2 position, b2World* world) : MyRectangle(width, height, al_map_rgb(200, 200, 200), position, world, false){
}
MyRectangle::MyRectangle(float32 width, float32 height, b2Vec2 position, b2World* world, bool dynamic) : MyRectangle(width, height, al_map_rgb(200, 200, 200), position, world, dynamic){
}
MyRectangle::MyRectangle(float32 width, float32 height, ALLEGRO_COLOR color, b2Vec2 position, b2World* world) : MyRectangle(width, height, color, position, world, false){
}
MyRectangle::MyRectangle(float32 width, float32 height, ALLEGRO_COLOR color, b2Vec2 position, b2World* world,bool dynamic)
{
	this->width = width;
	this->height = height;
	this->color = color;
	this->pos = position;
	this->dynamic = dynamic;
	b2BodyDef bodyDef;
	if (dynamic){


		bodyDef.position.Set(position.x, position.y);
		bodyDef.type = b2_dynamicBody;
		body = world->CreateBody(&bodyDef);
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(width/2,height/2);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);
	}
	else{
		bodyDef.position.Set(position.x, position.y);
		body = world->CreateBody(&bodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(width/2,height/2);
		body->CreateFixture(&groundBox, 0.0f);
	}

	body->SetUserData(this);

}



void MyRectangle::draw(){

	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();


	b2Vec2 cor(position.x - width / 2, position.y - height / 2);
	b2Vec2 cor1(position.x + width / 2, position.y - height / 2);
	b2Vec2 cor2(position.x + width / 2, position.y + height / 2);
	b2Vec2 cor3(position.x - width / 2, position.y + height / 2);

	Math::rotatePointByPoint(&cor, &position, angle);
	Math::rotatePointByPoint(&cor1, &position, angle);
	Math::rotatePointByPoint(&cor2, &position, angle);
	Math::rotatePointByPoint(&cor3, &position, angle);

	Camera::calculatePointOnScreen(&cor);
	Camera::calculatePointOnScreen(&cor1);
	Camera::calculatePointOnScreen(&cor2);
	Camera::calculatePointOnScreen(&cor3);

	Camera::calculatePointOnScreen(&position);
	al_draw_filled_triangle(cor.x, cor.y, cor1.x, cor1.y, cor2.x, cor2.y, color);
	al_draw_filled_triangle(cor.x, cor.y, cor2.x, cor2.y, cor3.x, cor3.y, color);
}

GameObject::GO_TYPES MyRectangle::getType(){
	return RECTANGLE;
}


std::string MyRectangle::serialize(){ 
	unsigned char r, b, g;
	al_unmap_rgb(color, &r, &g, &b);
	return "\"rect\":{\n\t\t\"pos\":[" + std::to_string(pos.x) + "," + std::to_string(pos.y) + "],\n" +
"\t\t\"size\":["+std::to_string(width)+","+std::to_string(height)+"],\n"+
"\t\t\"color\":[" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "],\n"+
"\t\t\"dynamic\":" + ((dynamic) ? "true":"false") +"}"; }