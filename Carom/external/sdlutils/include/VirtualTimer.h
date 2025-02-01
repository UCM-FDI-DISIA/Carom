// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <cassert>

/*
 * This class implements a virtual timer, i.e., a timer that can be paused and
 * resumed.
 */

class VirtualTimer {
public:

	VirtualTimer() {
		resetTime();
	}

	virtual ~VirtualTimer() {
	}

	// Reset the time to start counting from this instance.
	inline void resetTime() {
		_zeroTime = SDL_GetTicks();
		_currTime = 0;
		_deltaTime = 0;
		_paused = false;
	}

	// Return the current real time, i.e., the one elapsed since the
	// last time resetTime was called, taking into account the pause
	// periods.
	inline Uint32 currRealTime() const {
		return _paused ?
				_pauseStartRealTime - _zeroTime : SDL_GetTicks() - _zeroTime;
	}

	// Pause the timer
	inline void pause() {
		if (!_paused) {
			_paused = true;
			_pauseStartRealTime = SDL_GetTicks();
		}
	}

	// Resume the timer
	inline void resume() {
		if (_paused) {
			_zeroTime += (SDL_GetTicks() - _pauseStartRealTime);
			_paused = false;
		}
	}

	// Register the current time. It meant to be called at the begging of the game
	// loop, so objects can use the time of the current "simulation" step -- because
	// all objects should see the same time.
	//
	// It also calculate and store the delta-time which is the difference between the
	// current and last time.
	//
	inline Uint32 regCurrTime() {
		if (!_paused) {
			Uint32 currTime = currRealTime();
			_deltaTime = _currTime - currTime;
			_currTime = currTime;
		}
		return _currTime;
	}

	// Return the last registered time
	inline Uint32 currTime() const {
		return _currTime;
	}

	// Access the delta time, i.e., the difference between the last two game
	// loop iterations (two calls to regCurrTime)
	inline Uint32 deltaTime() const {
		return _deltaTime;
	}

private:
	bool _paused;
	Uint32 _zeroTime;
	Uint32 _pauseStartRealTime;
	Uint32 _currTime;
	Uint32 _deltaTime;
};

