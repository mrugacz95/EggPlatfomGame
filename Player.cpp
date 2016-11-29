#include "Player.h"
const float Player::radius = 2.f;
const float Player::maxVelocity = 5.f;
Player::Player(b2Vec2 pos, b2World* world)
{
	//	ASSERT(segments < MAX_BLOB_SEGMENTS)
	this->world = world;
	float angle_step = 2.0f *3.14f / (float)segments;
	float segment_length = 2.0f * radius * sinf(angle_step / 2.0f);
	float pointsSize=.3f;
	float innerCircle = 0.81f;
	// Create midpoint
	middlePoint = new MyCircle(radius/4, al_map_rgb(254, 170, 0), pos, world, true);
	middlePoint->getb2Body()->SetFixedRotation(true);
	//ksza³t sensora kolizji
	b2PolygonShape polyShape;
	b2Vec2 vec[5];
	vec[0].Set(-radius*1.2f,0);
	vec[1].Set(radius*1.2f,0);
	vec[2].Set(0,-radius*1.2f);
	double r = radius*1.2f*1.4142f / 2.f;  //45 st czyli pierw z 2
	vec[3].Set(r,-r);
	vec[4].Set(-r,-r);
	polyShape.Set(vec, 5);

	b2FixtureDef circleSensor;
	circleSensor.isSensor = true;
	circleSensor.shape = &polyShape;
	b2Fixture* circleSensorFix = middlePoint->getb2Body()->CreateFixture(&circleSensor);
	sensor = new Sensor();
	circleSensorFix->SetUserData(sensor);
	body = middlePoint->getb2Body();
	setColisionMask(middlePoint->getb2Body());
	float bx, by;
	// create outer point (which lie on a circle)
	for (int i = 0; i<segments; i++)
	{
		float angle = i * angle_step;
		bx = pos.x + radius * cos(angle);
		by = pos.y + radius * sin(angle);
		points[i] = new MyRectangle(pointsSize, pointsSize, b2Vec2(bx, by), world, true);

		setColisionMask(points[i]->getb2Body());

		//bx = pos.x + innerCircle * radius * cos(angle);
		//by = pos.y + innerCircle * radius * sin(angle);
		//points[i + segments] = new MyRectangle(pointsSize, pointsSize, b2Vec2(bx, by), world, true);

		//setColisionMask(points[i+segments]->getb2Body());
	}
	for (int i = 0; i < segments; i++)
		points[i]->getb2Body()->SetUserData(this);
	body->SetUserData(this);
	//link up with constraints
	b2DistanceJointDef jointDef;
	jointDef.collideConnected = true;
	jointDef.frequencyHz = 20.5f; //galeretowatoœæ
	jointDef.dampingRatio = 0.4f; //t³umienie
	for (int i = 0; i < segments; i++){
		int next = (i + 1) % segments;
		jointDef.Initialize(points[i]->getb2Body(), points[next]->getb2Body(),
			points[i]->getPos(), points[next]->getPos());
		joints[i] = (b2DistanceJoint*)world->CreateJoint(&jointDef);

	}
		jointDef.frequencyHz = 1.5f; //galeretowatoœæ
		jointDef.dampingRatio = 0.4f; //t³umienie
		for (int i = 0; i < segments; i++){
		int opposite = (i + segments / 2) % segments;
		int next2 = (i + 2) % segments;
		int next3 = (i + 3) % segments;
		jointDef.Initialize(points[i]->getb2Body(), points[next2]->getb2Body(),
			points[i]->getPos(), points[next2]->getPos());
		joints[i + segments] = (b2DistanceJoint*)world->CreateJoint(&jointDef);

		jointDef.Initialize(points[i]->getb2Body(), points[next3]->getb2Body(),
			points[i]->getPos(), points[next3]->getPos());
		joints[i + 2 * segments] = (b2DistanceJoint*)world->CreateJoint(&jointDef);

		jointDef.Initialize(points[i]->getb2Body(), points[opposite]->getb2Body(),
			points[i]->getPos(), points[opposite]->getPos());
		joints[i + 3 * segments] = (b2DistanceJoint*)world->CreateJoint(&jointDef);

		jointDef.Initialize(points[i]->getb2Body(), middlePoint->getb2Body(),
			points[i]->getPos(), middlePoint->getPos());
		joints[i + 4 * segments] = (b2DistanceJoint*)world->CreateJoint(&jointDef);


	}
	
}
void Player::draw(){
	b2Vec2 midPos;
	midPos.Set(middlePoint->getPos().x, middlePoint->getPos().y);
	Camera::calculatePointOnScreen(&midPos);
	//http://stackoverflow.com/questions/5271583/center-of-gravity-of-a-polygon
	//X = SUM[(Xi + Xi + 1) * (Xi * Yi + 1 - Xi + 1 * Yi)] / 6 / A
	//Y = SUM[(Yi + Yi + 1) * (Xi * Yi + 1 - Xi + 1 * Yi)] / 6 / A
	b2Vec2 cenMass;
	cenMass.SetZero();
	float A = 0;
	for (int i = 0; i < segments; i++){
		float p1x = points[i]->getPos().x, p1y = points[i]->getPos().y, p2x = points[(i + 1)%segments]->getPos().x, p2y = points[(i+1)%segments]->getPos().y;
		cenMass += b2Vec2((p1x + p2x) * (p1x * p2y - p2x * p1y), (p1y + p2y) * (p1x * p2y - p2x * p1y));
		A += p1x * p2y - p2x * p1y;
	}
	A /= 2.f;
	cenMass *= 1.f / (6 * A);
	for (int i = 0; i < segments; i++){
		b2Vec2 xy((float32)joints[i]->GetAnchorA().x, (float32)joints[i]->GetAnchorA().y);
		b2Vec2 xy1((float32)joints[i]->GetAnchorB().x, (float32)joints[i]->GetAnchorB().y);
		//wektor prostopad³y http://xion.org.pl/2008/01/29/wektor-prostopadly-do-danego/

		b2Vec2 vec1 = cenMass-xy;
		b2Vec2 vec2 = cenMass-xy1;
		vec1.Set(vec1.y, -vec1.x);
		vec2.Set(-vec2.y,vec2.x);
		vec1.Normalize();
		vec2.Normalize();
		vec1 *= 0.3f;
		vec2 *= 0.3f;
		vec1 += xy;
		vec2 += xy1;
		Camera::calculatePointOnScreen(&xy);
		Camera::calculatePointOnScreen(&xy1);
		Camera::calculatePointOnScreen(&vec1);
		Camera::calculatePointOnScreen(&vec2);

		al_draw_filled_triangle(xy.x, xy.y, xy1.x, xy1.y, midPos.x, midPos.y, al_map_rgb(255, 255, 255));
		float points[8]{ xy.x, xy.y, vec1.x, vec1.y, vec2.x, vec2.y, xy1.x, xy1.y };
		al_draw_spline(points, al_map_rgb(255, 255, 255), Camera::calculateLengthOnScreen(0.1f));
		al_draw_line(xy.x, xy.y, xy1.x, xy1.y, al_map_rgb(255, 255, 255), Camera::calculateLengthOnScreen(0.3f ));
		al_draw_filled_circle(xy.x,xy.y,Camera::calculateLengthOnScreen(0.3f/2.f), al_map_rgb(255, 255, 255));
	}
	//for (int i = segments; i < segments*2; i++){
	for (int i = 0; i < segments*5; i++){
		b2Vec2 xy((float32)joints[i]->GetAnchorA().x, (float32)joints[i]->GetAnchorA().y);
		b2Vec2 xy1((float32)joints[i]->GetAnchorB().x, (float32)joints[i]->GetAnchorB().y);
		Camera::calculatePointOnScreen(&xy);
		Camera::calculatePointOnScreen(&xy1);

		//al_draw_line(xy.x, xy.y, xy1.x, xy1.y, al_map_rgb(255, 0, 0), 1);
	}
	middlePoint->draw();
	Camera::calculatePointOnScreen(&cenMass);
	///al_draw_filled_circle(cenMass.x, cenMass.y, 3, al_map_rgb(0, 0, 0));

	//for (int i = 0; i < segments ; i++)
		//points[i]->draw();
	
}
void Player::jump(){
	if (sensor->getCollidersNum()>0){
		b2Vec2 jumpVec(0, 20);
		middlePoint->getb2Body()->ApplyLinearImpulse(jumpVec, middlePoint->getb2Body()->GetPosition(), true);
	}
}
void Player::moveLeft(){

	//if (middlePoint->getb2Body()->GetLinearVelocity().Length() < maxVelocity){
		b2Vec2 moveVec(-100, 0);
		middlePoint->getb2Body()->ApplyForceToCenter(moveVec, true);
	//}
}
void Player::moveRight(){
	//if (middlePoint->getb2Body()->GetLinearVelocity().Length() < maxVelocity){
		b2Vec2 moveVec(100, 0);
		middlePoint->getb2Body()->ApplyForceToCenter(moveVec, true);
	//}
}
Player::~Player()
{
	for (int i = 0; i < segments; i++){
		world->DestroyJoint(joints[i]);
		delete(points[i]);
		delete(middlePoint);
	}
	delete(sensor);
}
GameObject::GO_TYPES Player::getType(){
	return PLAYER;
}

void Player::addContact(std::string name){
	contacts.insert(name);
	//std::cout << "addcon" << name << " count"<< contacts.size()-1 << "\n";
	//for (auto str : contacts)
	//	std::cout << str << ", ";
	//std::cout << "\n";
}
void Player::subContact(std::string name){
	contacts.erase(name);
	//if (contacts.size()==1) std::cout << "not grounded\n";
	//else std::cout << "subcon " << name << " size " << contacts.size() << "\n";
}
void Player::setColisionMask(b2Body* body){
	b2Filter filter;
	filter.maskBits = 3; // 0000011b 
	filter.categoryBits = 4; // 000100b 
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		f->SetFilterData(filter);
	}
}
GameObject::GO_TYPES Player::Sensor::getType(){ return GameObject::SENSOR; }
void Player::Sensor::addCollider(){
	colidersNum++;
}
void Player::Sensor::subCollider(){
	colidersNum--;
}
int Player::Sensor::getCollidersNum(){
	return colidersNum;
}
std::string Player::Sensor::serialize(){ return ""; }
std::string Player::serialize(){ return "\"player\":{ \"pos\":[" + to_string(getPos().x) + "," + to_string(getPos().y) + "]}"; }
