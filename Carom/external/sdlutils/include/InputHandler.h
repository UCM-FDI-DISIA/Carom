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
 
	// ---- EVENTOS INPUTHANDLER ----.
	// close window event
	inline bool closeWindowEvent() {
		return _isCloseWindoEvent;
	}

	// keyboard
	inline bool keyDownEvent() {
		return _isKeyDownEvent;
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
		//std::cout << "Boton: " << _isMouseButtonDownEvent << "\n";
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

	// ---- EVENTOS HANDMADE (fijándome en los que ha creado Guillermo) ----.

	// para ver si el ratón hace clic sobre un rectángulo SDL.
	inline bool isMouseInRect(const std::pair<Sint32, Sint32>& mousePos, SDL_Rect& rect) {
		
		// NOTA: LAS COORDENADAS EN SDL VAN AL REVES.
		// derecha +x izquierda -x
		// abajo +y arriba -y
		
		Sint32 mouseX = _mousePos.first;
		Sint32 mouseY = _mousePos.second;

		return 
		mouseX >= rect.x  && mouseX <= rect.x + rect.w 
		&& mouseY >= rect.y && mouseY <= rect.y + rect.h;
	}

	// seleccionar bola del inventario.
	inline bool isBallSelectedUI(SDL_Rect ball) {
		_isBallSelectedUI = getMouseButtonState(LEFT)	   // se apreta el botón izquierdo
						    && mouseButtonDownEvent()   // se comprueba que se ha apretado
							&& (isMouseInRect(getMousePos(), ball)) // la posición donde hace clic es la de la bola.
							&& isOnUI();					   // además está en UI.

		return _isBallSelectedUI;
	}

	// se destruye la bola.
	inline bool isBallDestroyedUI(SDL_Rect ball){
		_isBallDestroyedUI = getMouseButtonState(RIGHT)  // se apreta el botón derecho.
							 && mouseButtonDownEvent()  	    // se comprueba que se ha apretado
							 && (isMouseInRect(getMousePos(), ball)) // la posición donde hace clic es la de la bola.
							 && isOnUI();					// además está en UI.

		return _isBallDestroyedUI;
	}

    // para lo de consultar las estadisticas de cada bola.
	inline bool isBallChecked(SDL_Rect ball){
		_checkBall = !mouseMotionEvent()             // si no se mueve el ratón.
					 && (isMouseInRect(getMousePos(), ball)); // y está sobre la pelota (no importa que esté en UI o no porque en los dos se comprueba).
					 
		return _checkBall;
	}

	// para seleccionar la bola en partida para arrastrar.
	inline bool isBallPickedIngame(SDL_Rect ball){
		_isBallPickedIngame = mouseButtonDownEvent()          // se apreta el mouse.
						      && getMouseButtonState(LEFT)    // en concreto el botón izquierdo.
						 	  && (isMouseInRect(getMousePos(), ball))  // en la posición donde está la bola.
						 	  && !isOnUI();                    // no ocurre en ventana de UI sino en partida.

		return _isBallPickedIngame;
	}

	// cuando se acciona el inventario.
	inline bool isInventoryOpened(SDL_Rect inventoryButton){
		_inventoryEvent = mouseButtonDownEvent() 		  // se apreta el mouse.
						  && getMouseButtonState(LEFT)    // en concreto el boton izquierdo.
					      && (isMouseInRect(getMousePos(), inventoryButton))  // la posicion donde hace clic es la del botón del inventario.
						  && !isOnUI()				      // no se ha abierto la UI.
					      ||							  // --- OR ---
						  keyDownEvent()				  // se comprueba que se presiona
				          && isKeyDown(SDLK_e)		      // se apreta la tecla E.			
					      && !isOnUI();					  // no se ha abierto la UI.

		return _inventoryEvent;
	}

	// cuando se acciona menú de pausa.
	inline bool isPauseMenuOpened(SDL_Rect pauseButton){
		_pauseMenuEvent = mouseButtonDownEvent()          // se apreta el mouse.
						  && getMouseButtonState(LEFT)	  // en concreto el botón izquierdo.
					      && (isMouseInRect(getMousePos(), pauseButton))  // la posición donde hace clic es la del botón de pausa.		
					      && !isOnUI()					  // no se ha abierto la UI.		
						  ||						      // --- OR ---
						  keyDownEvent()				  // se comprueba que se presiona
					      && isKeyDown(SDLK_ESCAPE)		  // se apreta la tecla ESC (¡¡¡OJO!!! igual esto hay que cambiarlo porque coincide con lo de "Cancelar botón" de la wiki).
						  && !isOnUI();					  // no se ha abierto la UI.

		return _pauseMenuEvent;
	}

	// aceptar boton / avanzar.
	inline bool isSubmitEvent(SDL_Rect acceptButton){
		_submitKeyEvent = mouseButtonDownEvent()  	       // se apreta el mouse.
						  && getMouseButtonState(LEFT)     // en concreto el boton izquierdo.
					      && (isMouseInRect(getMousePos(), acceptButton));  // la posición donde hace clic es la del botón a aceptar.

		return _submitKeyEvent;
	}

	// // cancelar boton / retroceder.
	inline bool isCancelEvent(){
		_cancelKeyEvent = isKeyDown(SDLK_ESCAPE) // le das al escape.
					      && isOnUI();            // con una ventana de UI abierta para cancelar.

		return _cancelKeyEvent;
	}

	// para activar/desactivar el modo UI (estás en/sobre interfaz o no).
	inline void toggleUI(){
		_isOnUI = !_isOnUI;
	}

	// ¿esta la ui activada?
	inline bool isOnUI(){
		return _isOnUI;
	}
	
	inline bool isWindowsFocused()
	{
		return _isWindowFocused;
	}

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
	/*
	+-----------------------------+-----------------------------------------------------+---------------------------+
	| Acción  					  | Input teclado y ratón 								| Contexto     				| 
	+-----------------------------+-----------------------------------------------------+---------------------------+
	| Reordenar bolas             | Clic izquierdo y arrastrar a una casilla            | Inventario       	   	    |
	| Destruir bolas              | Clic derecho sobre la bola                          | Inventario 				|
	| Consultar bolas             | Pasar el ratón por encima de la bola			    | Inventario y partida		|
	| Lanzar bola                 | Clic izquierdo sobre la bola, arrastrar y soltar	| Partida					|
	| Abrir inventario            | Clic izquierdo sobre botón de inventario o tecla e	| Partida (UI)				|
	| Abrir menú de pausa         | Clic izquierdo sobre botón de pausa o tecla esc		| Inventario y partida (UI) |
	| Aceptar botón / avanzar	  | Clic izquierdo sobre él								| UI						|
	| Cancelar botón / retroceder | Presionar tecla esc								    | UI			            |
	+-----------------------------+-----------------------------------------------------+---------------------------+
    */
	// cuando te encuentras o se trata de algo referente a la UI (no en partida).
	bool _isOnUI = false; // inicialmente false hasta que se abra algo de UI.	

	bool _isBallSelectedUI; 	// seleccionar bola del inventario.
	bool _isBallMovingUI; 		// arrastar bola del inventario.
	bool _isBallDestroyedUI;    // se destruye la bola.
	bool _checkBall; 			// para lo de consultar las estadisticas de cada bola.
	bool _isBallPickedIngame;   // para seleccionar la bola en partida para arrastrar. 
	bool _isBallDraggingIngame; // para arrastrar la bola.	
	bool _isBallThrowingIngame; // para soltar la bola.	
	bool _inventoryEvent; 		// cuando se acciona el inventario.
	bool _pauseMenuEvent; 		// cuando se acciona menú de pausa. 
	bool _submitKeyEvent; 		// aceptar boton / avanzar.	
	bool _cancelKeyEvent; 		// cancelar boton / retroceder.

	bool _isWindowFocused;
	//Vector2D _navigateVectorEvent;


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
		case SDL_WINDOWEVENT_MINIMIZED:
			_isWindowFocused = false;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			_isWindowFocused = true;
			break;
		case SDL_WINDOWEVENT_ENTER:
			_isWindowFocused = true;
			break;
		default:
			break;
		}
	}
};


// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::Instance();
}
