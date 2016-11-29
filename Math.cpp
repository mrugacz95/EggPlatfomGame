#include "Math.h"

//p'x = cos(theta) * (px-ox) - sin(theta) * (py-oy) + ox
//p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy
void Math::rotatePointByPoint(b2Vec2* point, b2Vec2* o, float32 theta){
	b2Vec2 pos(point->x, point->y);
	float s = sin(theta);
	float c = cos(theta);
	point->x = c * (pos.x - o->x) - s * (pos.y - o->y) + o->x;
	point->y = s * (pos.x - o->x) + c * (pos.y - o->y) + o->y;
}

//http://xion.org.pl/2011/10/27/kod-ci-wszystko-wytlumaczy/
float Math::InvSqrt(float x){
	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x*(1.5f - xhalf*x*x);
	return x;
}
void Math::scalePointByPoint(b2Vec2& point, b2Vec2* o, float scale){
	if (scale != 1.f){
		//float32 dist = (point.x - o->x)*(point.x - o->x) + (point.y - o->y)*(point.y - o->y);
		//float32 scaled = dist*scale*InvSqrt(dist);
		//float32 a = point.x;
		//point.Set(point.x*scale,(float32) point.y*scale);

		int b = 0;
		
		b2Vec2 vec = point - *o;
		vec.Normalize();
		point *= scale / vec.LengthSquared();
		

	}
}
void Math::addPositions(b2Vec2* point, b2Vec2* point2){
	*point = *point + *point2;
}