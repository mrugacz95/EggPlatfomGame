#pragma once
#include <Box2D\Box2D.h>
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include "ModelManager.h"
#include "Pickable.h"
class PlayingState;// ??
class MyContactListener : public b2ContactListener
{
	public:
		MyContactListener(PlayingState* playingState, ModelManager *modelManager);
	private:
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
		PlayingState *playingState;
		ModelManager *modelManager;
};

