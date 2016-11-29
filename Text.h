#pragma once
#include "GameObject.h"
#include "Camera.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class Text : public GameObject
{
public:
	Text(b2Vec2 pos, ALLEGRO_COLOR color, std::string text, ALLEGRO_FONT* font, bool isStickedToScreen);
	void setColor(ALLEGRO_COLOR color);
	void draw();
	std::string serialize() override;
	GameObject::GO_TYPES getType() override;
private:
	ALLEGRO_COLOR color;
	std::string text;
	b2Vec2 pos;
	ALLEGRO_FONT* font;
	bool isStickedToScreen;
};
