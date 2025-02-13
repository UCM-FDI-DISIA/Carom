// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include <box2D/box2D.h>
#include "Manager.h"

// class Container;
// class Entity;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();

private:

	ecs::Manager *_mngr;
	b2WorldId _worldId;

	// std::vector<Entity*> _objs;
};

