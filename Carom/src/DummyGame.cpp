#include "DummyGame.h"

#include "SDLUtils.h"
#include "InputHandler.h"

#include "gameList.h"
#include "GameScene.h"
#include "EntityManager.h"
#include "Entity.h"
#include "TransformComponent.h"

DummyGame::DummyGame() {}

DummyGame::~DummyGame() {}

// TODO
void
DummyGame::init() {
    // initialize SDL singleton
	if (!SDLUtils::Init("Ping Pong", 800, 600,
			"../../resources/config/sdlutilsdemo.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return;
	}

	// initialize InputHandler singleton
    if (!InputHandler::Init()) {
        std::cerr << "Something went wrong while initializing SDLHandler"
                << std::endl;
        return;
    }

}

void
DummyGame::start() {
    bool exit = false;

    GameList<ecs::Entity> glist;
    ecs::EntityManager *_enttmngr = new ecs::EntityManager(&glist);

    _enttmngr->createWhiteBall({10, 10}, b2_dynamicBody, 1.0f, 1.0f, 1.0f, 10);
    ecs::Entity* white_ball = _enttmngr->getEntities(ecs::grp::WHITEBALL)[0];
    std::cout << "Tiene transform: " << white_ball->tryGetComponent<ecs::TransformComponent>() << std::endl;
    _enttmngr->removeComponent<ecs::TransformComponent>(white_ball);
    std::cout << "Tiene transform: " << white_ball->tryGetComponent<ecs::TransformComponent>() << std::endl;
    
    // recoger input

    while(!exit) {

    }

}