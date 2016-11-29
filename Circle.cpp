#include "Circle.h"

MyCircle::MyCircle(float radius, ALLEGRO_COLOR color, b2Vec2 position, b2World* world, bool dynamic)
{
	this->radius = radius;
	this->color = color;
	this->dynamic = dynamic;
	if (dynamic){


		b2BodyDef bodyDef;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.type = b2_dynamicBody;
		body = world->CreateBody(&bodyDef);
		b2CircleShape dynamicBody;
		dynamicBody.m_p.Set(0, 0);
		dynamicBody.m_radius = radius;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBody;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);
	}
	else{
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(position.x, position.y);
		body = world->CreateBody(&groundBodyDef);
		b2CircleShape groundBody;
		groundBody.m_p.Set(0, 0);
		groundBody.m_radius = radius;
		body->CreateFixture(&groundBody, 0.0f);
	}
}
void MyCircle::draw(){

	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();



	Camera::calculatePointOnScreen(&position);
	al_draw_filled_circle(position.x, position.y, Camera::calculateLengthOnScreen(radius) , color);
	
}
GameObject::GO_TYPES MyCircle::getType(){
	return CIRCLE;
}
std::string MyCircle::serialize(){	

	unsigned char r, b, g;
	al_unmap_rgb(color, &r, &g, &b); 
	return "\"circle\":{\n\t\t\"size\":" + to_string(radius) + ","+
"\n\t\t\"pos\":[" + std::to_string(getPos().x) + "," + std::to_string(getPos().y) + "],\n" +
"\t\t\"color\":[" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "],\n" + 
"\t\t\"dynamic\":" + ((dynamic) ? "true" : "false") + "}";
}
