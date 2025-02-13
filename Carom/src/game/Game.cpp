// This file is part of the course TPV2@UCM - Samir Genaim


// #include "../external/sdlutils/include/InputHandler.h"
// #include "../external//sdlutils/include/SDLUtils.h"
#include <InputHandler.h>
#include <SDLUtils.h>
#include "ecs.h"
// #include "../utils/Collisions.h"

#include "Game.h"
#include "Manager.h"
// #include "Container.h"
// #include "ImageRenderer.h"
// #include "GameManager.h"
// #include "AIPaddle.h"
// #include "BounceOnBorder.h"
// #include "EmptyRectangleRenderer.h"
// #include "GameCtrl.h"
// #include "ImageRenderer.h"
// #include "InfoMsgs.h"
// #include "MovePaddleWithKeyBoard.h"
// #include "MovePaddleWithMouse.h"
// #include "RectangleRenderer.h"
// #include "ScoreRenderer.h"
// #include "SimpleMove.h"
// #include "StopOnBorder.h"
// #include "FighterCtrl.h"
// #include "DeAcceleration.h"
// #include "ShowAtOppositeSide.h"

Game::Game() :
		_mngr(nullptr)
        //,
		// _fighter(nullptr)
{ }

Game::~Game() {
	// delete all game objects
	// for (GameObject *o : _objs) {
	// 	delete o;
	// }

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
	_mngr = new ecs::Manager();
	_mngr->addEntity(ecs::obj::WHITEBALL);


    // ! WORLD
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 10.0f};
    _worldId = b2CreateWorld(&worldDef);



	// _ball = new Container;
	// _ball->addComponent(new ImageRenderer(&sdlutils().images().at("tennis_ball")));
    // _ball->addPhysicalComponents(_worldId, 10, 10, b2_dynamicBody);

	// _ball->setWidth(50.0f);
	// _ball->setHeight(50.0f);
	// // _ball->getPos().set(sdlutils().width() / 2, sdlutils().height() / 2);

	// _objs.push_back(_ball);

	// // ? BALL 2
	// _ball_2 = new Container;
	// _ball_2->addComponent(new ImageRenderer(&sdlutils().images().at("tennis_ball")));
    // _ball_2->addPhysicalComponents(_worldId, 13, 30, b2_staticBody);

	// _ball_2->setWidth(50.0f);
	// _ball_2->setHeight(50.0f);
	// // _ball->getPos().set(sdlutils().width() / 2, sdlutils().height() / 2);

	// _objs.push_back(_ball_2);

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
		_mngr->update();

		// input
		// for (auto &o : _objs) {
		// 	o->handleInput();
		// }

		// update
		// for (auto &o : _objs) {
		// 	o->update();
		// }

		
		sdlutils().clearRenderer();

		// render
		_mngr->render();
		// for (auto &o : _objs) {
		// 	o->render();
		// }

		sdlutils().presentRenderer();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}
