// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <cassert>

#include "Singleton.h"

// Instead of a Singleton class, we could make it part of
// SDLUtils as well.

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
	}

	inline bool keyUpEvent() {
		return _isKeyUpEvent;
	}

	inline bool isKeyDown(SDL_Scancode key) {
		return _kbState[key] == 1;
	}

	inline bool isKeyDown(SDL_Keycode key) {
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

	// TODO add support for Joystick, see Chapter 4 of
	// the book 'SDL Game Development'

private:
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

	inline void onKeyDown(const SDL_Event&) {
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

	inline void handleWindowEvent(const SDL_Event &event) {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			_isCloseWindoEvent = true;
			break;
		default:
			break;
		}
	}

	bool _isCloseWindoEvent;
	bool _isKeyUpEvent;
	bool _isKeyDownEvent;
	bool _isMouseMotionEvent;
	bool _isMouseButtonUpEvent;
	bool _isMouseButtonDownEvent;
	std::pair<Sint32, Sint32> _mousePos;
	std::array<bool, 3> _mbState;
	const Uint8 *_kbState;
}
;

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::Instance();
}
