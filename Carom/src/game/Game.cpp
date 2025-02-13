#include <InputHandler.h>
#include <SDLUtils.h>
#include "ecs.h"

#include "Game.h"
#include "EntityManager.h"

Game::Game() : _enttmngr(nullptr)
{ 
}

Game::~Game() {
	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

void Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("JUEGO", 800, 600, "..\\..\\resources\\config\\test.resources.json")) {
		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return;
	}

    // ! MANAGER
	_enttmngr = new ecs::EntityManager();
	_enttmngr->addEntity(ecs::obj::WHITEBALL);

    // ! WORLD
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 10.0f};
    _worldId = b2CreateWorld(&worldDef);

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {

		// store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

        // ! WORLD
        // _b2World->update();
        static constexpr float _timeStep = 1.0f / 60.0f;
        static constexpr int _subStepCount = 4;
        b2World_Step(_worldId, _timeStep, _subStepCount);

		// ! MANAGER
		_enttmngr->update();
		
		sdlutils().clearRenderer();

		// render
		_enttmngr->render();

		sdlutils().presentRenderer();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}
