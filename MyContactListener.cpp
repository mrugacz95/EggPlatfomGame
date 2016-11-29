#include "MyContactListener.h"
#include "PlayingState.h"

MyContactListener::MyContactListener(PlayingState* playingState, ModelManager *modelManager) 
{
	this->playingState = playingState;
	this->modelManager = modelManager;
}
//http://www.iforce2d.net/b2dtut/collision-callbacks
void MyContactListener::BeginContact(b2Contact* contact){
	void* data = contact->GetFixtureA()->GetBody()->GetUserData();
	void* data1 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (data)
		switch (static_cast<GameObject*>(data)->getType())
		{
			case GameObject::PLAYER:
				if (data1)
					static_cast<Player*>(data)->addContact(static_cast<GameObject*>(data1)->getName());
				break;
 			case GameObject::PICKABLE:
				if (static_cast<GameObject*>(data1)->getType() == GameObject::PLAYER){
					modelManager->delGameObject(static_cast<Pickable*>(data)->getName());
					playingState->addPoints(1);
				}
				break;
			case GameObject::RECTANGLE:
				//std::cout << "kwadrat\n";
				break;
			case GameObject::SENSOR:
				static_cast<Player::Sensor*>(data)->addCollider();
				break;

	}
	if (data1)
		switch (static_cast<GameObject*>(data1)->getType())
		{
		case GameObject::PLAYER:
			if (data)
				static_cast<Player*>(data1)->addContact(static_cast<GameObject*>(data1)->getName());
			break;
		case GameObject::PICKABLE:
			if (static_cast<GameObject*>(data)->getType() == GameObject::PLAYER){
				modelManager->delGameObject(static_cast<Pickable*>(data1)->getName()); 
				playingState->addPoints(1);
			}
			break;
		case GameObject::RECTANGLE:
			//std::cout << "prostokat\n";
			break;
		case GameObject::SENSOR:
			static_cast<Player::Sensor*>(data1)->addCollider();
			break;

		}

	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if (fixtureUserData)
	if (static_cast<GameObject*>(fixtureUserData)->getType() == GameObject::SENSOR)
		static_cast<Player::Sensor*>(fixtureUserData)->addCollider();

	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if (fixtureUserData)
	if (static_cast<GameObject*>(fixtureUserData)->getType() == GameObject::SENSOR)
	static_cast<Player::Sensor*>(fixtureUserData)->addCollider();
	
}

void MyContactListener::EndContact(b2Contact* contact){

	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if (fixtureUserData)
	if (static_cast<GameObject*>(fixtureUserData)->getType() == GameObject::SENSOR)
		static_cast<Player::Sensor*>(fixtureUserData)->subCollider();

	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if (fixtureUserData)
	if (static_cast<GameObject*>(fixtureUserData)->getType() == GameObject::SENSOR)
		static_cast<Player::Sensor*>(fixtureUserData)->subCollider();
}