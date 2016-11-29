#include "Camera.h"
float Camera::zoom = 16.f;
float Camera::rotation = .0f; //radians
b2Vec2 Camera::cameraPos = b2Vec2(0,0);
b2Vec2* Camera::calculatePointOnScreen(b2Vec2* point){
	Math::rotatePointByPoint(point, &cameraPos,rotation);
	Math::scalePointByPoint(*point, &cameraPos, zoom);
	Math::addPositions(point,&cameraPos);
	point->x = screenWidth / 2 + point->x;
	point->y = screenHeight / 2 - point->y;
	return point;
};
b2Vec2 Camera::calculatePointInWorld(b2Vec2 pos){
	pos.x -= screenWidth / 2.f;
	pos.y -= screenHeight / 2.f;
	pos.y *= -1;
	pos -= cameraPos;
	pos *= 1 / (float32)zoom;
	Math::rotatePointByPoint(&pos,&cameraPos,-rotation);

	return b2Vec2(pos.x,pos.y);

}
int Camera::getScreenWidth(){
	return screenWidth;
}
int Camera::getScreenHeight(){
	return screenHeight;
}
void Camera::moveCamera(int x, int y){
	cameraPos += b2Vec2(x, y);
}
void Camera::setZoom(float zoom){
	if (zoom < 0)
		zoom = -1 / zoom;
	Camera::zoom = zoom;
}
void Camera::zoomIn(float multipler){
	cameraPos.Set(cameraPos.x*multipler, cameraPos.y*multipler);
	zoom *= abs(multipler);
}

void Camera::zoomOut(float multipler){

	Camera::cameraPos.Set(cameraPos.x/multipler, cameraPos.y/multipler);
	Camera::zoom /= abs(multipler);
}
float32 Camera::calculateLengthOnScreen(float l){
	return l*zoom;
}
float Camera::calculateLengthInWorld(float l){
	return l/zoom;
}
b2Vec2 Camera::getCameraPos(){
	return cameraPos;
}
void Camera::setCameraPos(b2Vec2 pos){
	//TODO bezw³adnoœæ kamery
	cameraPos.Set(-pos.x*zoom, -pos.y*zoom);
	//minusy wynikaj¹ z tego ¿e to nie kamera siê porusza tylko zaczyna przeliczaæ punkty w innych miejscach
}