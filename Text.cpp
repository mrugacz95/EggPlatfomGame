#include "Text.h"

Text::Text(b2Vec2 pos, ALLEGRO_COLOR color, std::string text, ALLEGRO_FONT* font, bool isStickedToScreen){
	this->text = text;
	this->pos = pos;
	this->color = color;
	this->isStickedToScreen = isStickedToScreen;
	this->font = font;

}
void Text::draw(){
	if (!isStickedToScreen)
		
		al_draw_text(font,color,pos.x,pos.y,ALLEGRO_ALIGN_CENTER, text.c_str());
	else{
		b2Vec2 onScr;
		onScr.Set(pos.x,pos.y);
		Camera::calculatePointOnScreen(&onScr);
		al_draw_text(font, color, onScr.x, onScr.y, ALLEGRO_ALIGN_CENTER, text.c_str());
	}
		
}
void Text::setColor(ALLEGRO_COLOR color){
	this->color = color;
}
/*void Text::Serialize(PrettyWriter<FileStream>& writer){

	writer.StartObject();
	writer.String("text");
	writer.StartArray();


	writer.StartObject();
	writer.String("posX");
	writer.Double(pos.x);
	writer.EndObject();

	writer.StartObject();
	writer.String("posY");
	writer.Double(pos.y);
	writer.EndObject();

	writer.String("text");
	writer.String(text.c_str());
	writer.EndArray();
	writer.EndObject();
}*/
GameObject::GO_TYPES Text::getType(){
	return TEXT;
}
std::string Text::serialize(){
	unsigned char r, b, g;
	al_unmap_rgb(color, &r, &g, &b); 
	return "\"text\":{\n\t\t\"pos\":[" + std::to_string(pos.x) + "," + std::to_string(pos.y) + "],\n" +
"\t\t\"color\":[" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "],\n" +
"\t\t\"text\":\"" + text + "\",\n" +
"\t\t\"stickedToScreen\":" + ((isStickedToScreen) ? "true" : "false") +
"}"; }