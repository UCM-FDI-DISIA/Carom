// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <cassert>
#include "Vector2D.h"

#include "Singleton.h"

// Instead of a Singleton class, we could make it part of
// SDLUtils as well.

// COMO NO HAY OBJETOS QUE TESTEAR QUE MUESTRE POR CONSOLA COSAS CUANDO SE ACCIONEN LAS MOVIDAS.
class InputHandler: public Singleton<InputHandler> {

	friend Singleton<InputHandler> ;

public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE, RIGHT, _LAST_MOUSEBUTTON_VALUE
	};


	// clear the state
	inline void clearState() {
		_isCloseWindoEvent = false;
		_isKeyDownEvent = false;
		_isKeyUpEvent = false;

		_isMouseButtonUpEvent = false;
		_isMouseButtonDownEvent = false;

		_isMouseMotionEvent = false;
	}

	// update the state with a new event
	inline void update(const SDL_Event &event) {
		switch (event.type) {
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_WINDOWEVENT:
			handleWindowEvent(event);
			break;

			
		default:
			break;
		}
	}

	// refresh
	inline void refresh() {
		SDL_Event event;

		clearState();
		while (SDL_PollEvent(&event))
			update(event);
	}
 
	// close window event
	inline bool closeWindowEvent() {
		return _isCloseWindoEvent;
	}

	// keyboard
	inline bool keyDownEvent() {
		return _isKeyDownEvent;
		/*
			AÑADIR CASOS PARA LLAMAR A METODOS
			*/
	}

	inline bool keyUpEvent() {
		return _isKeyUpEvent;
	}

	inline bool isKeyDown(SDL_Scancode key) {
		return _kbState[key] == 1;
	}

	inline bool isKeyDown(SDL_Keycode key) {
		switch (key)
		{
		case SDLK_e: // añadir caso de clic cuando haya botón de inventario.
			_inventoryEvent = true; // abre inventario
			break;

		case SDLK_ESCAPE: // añadir caso de clic cuando haya botón de pausa. Caso 
			_pauseMenuEvent = true; // abre inventario
			break;
		
		default:
			break;
		}
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyUp(SDL_Scancode key) {
		return _kbState[key] == 0;
	}

	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	// mouse
	inline bool mouseMotionEvent() {
		return _isMouseMotionEvent;
	}

	inline bool mouseButtonEvent() {
		return _isMouseButtonUpEvent || _isMouseButtonDownEvent;
	}

	inline bool mouseButtonUpEvent() {
		return _isMouseButtonUpEvent;
	}

	inline bool mouseButtonDownEvent() {
		return _isMouseButtonDownEvent;
	}

	inline const std::pair<Sint32, Sint32>& getMousePos() {
		return _mousePos;
	}

	inline int getMouseButtonState(uint8_t b) {
		assert(b < _LAST_MOUSEBUTTON_VALUE);
		return _mbState[b];
	}

	// TODO add support for Joystick, see Chapter 4 of the book 'SDL Game Development'

	// ---- Eventos creados de cara al juego (fijándome en los que ha creado Guillermo) ----.
	// ---- UI.
	inline bool isInventoryActivated(){ return _inventoryEvent; }
	inline bool isPauseMenuActivated(){ return _pauseMenuEvent; }
	inline bool isBallDestroyed(){ return _isBallDestroyed; }


	
	/*inline bool isKeySubmitting(){
		return _submitKeyEvent;
	}

	inline bool isKeyCancelling(){
		return _cancelKeyEvent;
	}

	inline bool isKeyPausing(){
		return _pausedKeyEvent;
	}

	inline Vector2D getNavigationDirection(){
		return _navigateVectorEvent;
	}*/

private:
	// ---- VARS DE INPUTHANDLER ----.
	bool _isCloseWindoEvent;
	bool _isKeyUpEvent;
	bool _isKeyDownEvent;
	bool _isMouseMotionEvent;
	bool _isMouseButtonUpEvent;
	bool _isMouseButtonDownEvent;

	std::pair<Sint32, Sint32> _mousePos;
	std::array<bool, 3> _mbState;
	const Uint8 *_kbState;

	// ---- VARS HANDMADE (reciclando los que ha creado Guillermo) ----.

	// cuando te encuentras o se trata de algo referente a la UI (no en partida).
	bool _isOnUI = false; // inicialmente false hasta que se abra algo de UI.

	// posición de ejemplo (no sirve para nada ahora).
	std::pair<Sint32, Sint32> a_prueba = {1, 1};

	// cuando se acciona el inventario.
	bool _inventoryEvent = mouseButtonDownEvent() 		  // se apreta el mouse.
						   && getMouseButtonState(LEFT)   // en concreto el boton izquierdo.
						   && (getMousePos() == a_prueba) // la posicion donde hace clic es la del botón del inventario.
						   && !_isOnUI				      // no se ha abierto la UI.
						   ||							  // --- OR ---
						   isKeyDown(SDLK_e)		      // se apreta la tecla E.			
						   && !_isOnUI;					  // no se ha abierto la UI.

	// cuando se acciona menú de pausa
	bool _pauseMenuEvent = mouseButtonDownEvent()
						   && getMouseButtonState(LEFT)
						   && (getMousePos() == a_prueba) // la posición donde hace clic es la del botón de pausa.		
						   && !_isOnUI					  // no se ha abierto la UI.		
						   ||							  // --- OR ---
						   isKeyDown(SDLK_ESCAPE)		  // se apreta la tecla ESC (¡¡¡OJO!!! igual esto hay que cambiarlo porque coincide con lo de "Cancelar botón" de la wiki).
						   && !_isOnUI;					  // no se ha abierto la UI.

	// se destruye la bola.
	bool _isBallDestroyed = mouseButtonDownEvent()  			// se apreta el mouse.
							&& getMouseButtonState(RIGHT) 		// en concreto el boton derecho.
							&& (getMousePos() == a_prueba)		// la posición donde hace clic es la de la bola.
							&& _isOnUI;							// además está en UI.

	/*//esto ya son eventos mios (Guillermo).
	// Hola soy Carmen lo he comentado porque voy a renamearlo.
	bool _submitKeyEvent;
	bool _cancelKeyEvent;
	bool _pausedKeyEvent;
	
	Vector2D _navigateVectorEvent;*/



	InputHandler() {
		_kbState = nullptr;
		clearState();
	}

	virtual ~InputHandler() {
	}

	inline bool init() {
		_kbState = SDL_GetKeyboardState(0);
		assert(_kbState != nullptr);
		return true;
	}

	inline void onKeyDown(const SDL_Event& event) {
		_isKeyDownEvent = true;
	}

	inline void onKeyUp(const SDL_Event&) {
		_isKeyUpEvent = true;
	}

	inline void onMouseMotion(const SDL_Event &event) {
		_isMouseMotionEvent = true;
		_mousePos.first = event.motion.x;
		_mousePos.second = event.motion.y;

	}

	inline void onMouseButtonDown(const SDL_Event &event) {
		_isMouseButtonDownEvent = true;
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			_mbState[LEFT] = true;
			break;
		case SDL_BUTTON_MIDDLE:
			_mbState[MIDDLE] = true;
			break;
		case SDL_BUTTON_RIGHT:
			_mbState[RIGHT] = true;
			break;
		default:
			break;
		}
	}

	inline void onMouseButtonUp(const SDL_Event &event) {
		_isMouseButtonUpEvent = true;
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			_mbState[LEFT] = false;
			break;
		case SDL_BUTTON_MIDDLE:
			_mbState[MIDDLE] = false;
			break;
		case SDL_BUTTON_RIGHT:
			_mbState[RIGHT] = false;
			break;
		default:
			break;
		}
	}

	// ---- No tocar de momento..
	inline void handleWindowEvent(const SDL_Event &event) {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			_isCloseWindoEvent = true;
			break;
		default:
			break;
		}
	}
}
;

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::Instance();
}
