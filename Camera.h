#pragma once
#include <Box2D\Box2D.h>
#include "Math.h"
class Camera
{
public:

	static b2Vec2* calculatePointOnScreen(b2Vec2* point);
	static int getScreenWidth();
	static int getScreenHeight();
	static void moveCamera(int x, int y);
	static void setZoom(float zoom);
	static void zoomIn(float mulitpler);
	static void zoomOut(float multipler);
	static float calculateLengthOnScreen(float l);
	static float calculateLengthInWorld(float l);
	static b2Vec2 getCameraPos();
	static void setCameraPos(b2Vec2 pos);
	static b2Vec2 calculatePointInWorld(b2Vec2 pos);
private:
	static void scale(b2Vec2* point);
	static void move(b2Vec2* point);
	static b2Vec2 cameraPos;
	static float zoom;
	static float rotation;
	static const int screenWidth=640;
	static const int screenHeight=480;
};