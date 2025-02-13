#pragma once

#include <vector>
#include <box2D/box2D.h>
#include "EntityManager.h"

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();

private:
	ecs::EntityManager *_enttmngr;
	b2WorldId _worldId;
};
