#pragma once
#include <Box2D\Box2D.h>
class Math
{
public:
	static void rotatePointByPoint(b2Vec2* point, b2Vec2* o, float32 theta);
	static void scalePointByPoint(b2Vec2& point, b2Vec2* o, float32 scale);
	static float InvSqrt(float x);
	static void addPositions(b2Vec2* point, b2Vec2* o);
};
