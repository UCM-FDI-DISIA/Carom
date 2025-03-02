// This file is part of the course TPV2@UCM - Samir Genaim

#include <SDL.h>

#include "sdlutils_demo.h"

#include "InputHandler.h"
#include "macros.h"
#include "SDLUtils.h"

using namespace std;

void input_basic_demo() {

	// Initialize the SDLGame singleton
	if (!SDLUtils::Init("Carom Input Test", 800, 600,
			"../../resources/config/sdlutilsdemo.resources.json")) {
		std::cerr << "Something went wrong while initializing SDLUtils!"
				<< std::endl;
		return;
	}

	// Initialize the input handler
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing InputHandler!"
				<< std::endl;
		return;

	}

	// reference to the SDLUtils Singleton. You could use it as a pointer as well,
	// I just prefer to use . instead of ->, it is just a matter of taste, nothing
	// else!
	//
	// you can also use the inline method sdlutils() that simply returns the value
	// of *SDLUtils::instance() --- it is defined at the end of SDLUtils.h
	//
	auto &sdl = *SDLUtils::Instance();

	//show the cursor
	sdl.showCursor();

	// store the 'renderer' in a local variable, just for convenience
	SDL_Renderer *renderer = sdl.renderer();

	// we can take textures from the predefined ones, and we can create a custom one as well
	auto &sdlLogo = sdl.images().at("sdl_logo");
	auto &helloSDL = sdl.msgs().at("HelloSDL");
	Texture pressAnyKey(renderer, "Press cancel key <<esc>> to exit",
			sdl.fonts().at("ARIAL24"), build_sdlcolor(0x112233ff),
			build_sdlcolor(0xffffffff));
	auto &ball = sdl.images().at("star"); // la bola
	auto &inventory = sdl.images().at("pacman"); // boton de inventario.
	auto &pause = sdl.images().at("heart"); // boton de pausa.

	SDL_Rect ballRect;
	ballRect.x = 500;
	ballRect.y = 500;
	ballRect.w = ball.width();
	ballRect.h = ball.height();

	SDL_Rect inventoryRect;
	inventoryRect.x = 100;
	inventoryRect.y = 100;
	inventoryRect.w = inventory.width();
	inventoryRect.h = inventory.height();

	SDL_Rect pauseRect;
	pauseRect.x = 300;
	pauseRect.y = 100;
	pauseRect.w = pause.width();
	pauseRect.h = pause.height();

	// some coordinates
	auto winWidth = sdl.width();
	auto winHeight = sdl.height();
	auto x0 = (winWidth - pressAnyKey.width()) / 2;
	auto y0 = (winHeight - pressAnyKey.height()) / 2;
	auto x1 = 0;
	auto y1 = y0 - 4 * pressAnyKey.height();
	auto x2 = (winWidth - sdlLogo.width()) / 2;
	auto y2 = y0 + 2 * pressAnyKey.height();

	// start the music in a loop
	sdl.musics().at("beat").play();

	// reference to the input handler (we could use a pointer, I just . rather than ->).
	// you can also use the inline method ih() that is defined in InputHandler.h
	auto &ih = *InputHandler::Instance();

	// a boolean to exit the loop
	bool exit_ = false;

	while (!exit_) {
		Uint32 startTime = sdl.currRealTime();

		// NOTA: DIGAMOS QUE LA ESTRELLA ES LA BOLA.

		// update the event handler
		ih.refresh();

		// si se presiona la u (además comprueba que se ha presionado tecla para que no se haga muy rápido y toglee varias veces...)
		if (ih.keyDownEvent() && ih.isKeyDown(SDLK_u) ){
			ih.toggleUI(); // activa o desactiva la UI.
			if(ih.isOnUI()) std::cout << "Modo UI activado." << std::endl;
			else std::cout << "Modo UI desactivado" << std::endl;	
		}

		// cancelar evento: en este caso cierra la ventana si la UI está activada.
		if(ih.isCancelEvent()){
			std::cout << "Evento de cancelar activado." << std::endl;
			exit_ = true;
		}

		// Con el UI activado seleccionar bola.
		if(ih.isBallSelectedUI(ballRect)){
			std::cout << "Se ha seleccionado una bola del inventario." << std::endl;
		}

		// Con el UI activado seleccionar bola.
		if(ih.isBallDestroyedUI(ballRect)){
			std::cout << "Se ha destruido una bola del inventario." << std::endl;
		}

		// Comprueba las estadísticas de la bola
		if(ih.isBallChecked(ballRect)){
			if(ih.isOnUI()) std::cout << "Se comprueban las estadísticas de la bola (en UI)." << std::endl;
			else std::cout << "Se comprueban las estadísticas de la bola (sin UI)." << std::endl;
		}

		// Se selecciona la bola blanca en partida
		if(ih.isBallPickedIngame(ballRect)){
			std::cout << "Se ha seleccionado la bola en partida." << std::endl;
		}

		// Abre el inventario cuando no esta abierto (no esta UI activada).
		if(ih.isInventoryOpened(inventoryRect)){
			std::cout << "Se ha abierto el inventario." << std::endl;
		}

		// Abre el menu de pausa cuando no esta abierto (no esta UI activada).
		if(ih.isPauseMenuOpened(pauseRect)){
			std::cout << "Se ha abierto el menú de pausa." << std::endl;
		}

		// clear screen
		sdl.clearRenderer();

		// star render.
		ball.render(500, 500);
		inventory.render(100, 100);
		pause.render(300, 100);

		// render Hello SDL
		helloSDL.render(x1, y1);
		if (x1 + helloSDL.width() > winWidth)
			helloSDL.render(x1 - winWidth, y1);
		x1 = (x1 + 5) % winWidth;

		// render Press Any Key
		pressAnyKey.render(x0, y0);

		// render the SDLogo
		sdlLogo.render(x2, y2);

		// present new frame
		sdl.presentRenderer();

		Uint32 frameTime = sdl.currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// stop the music
	Music::haltMusic();

	// Release InputHandler and then SDLUtils (initialization reverse order)
	if (InputHandler::HasInstance())
		InputHandler::Release();
	if (SDLUtils::HasInstance())
		SDLUtils::Release();

}

