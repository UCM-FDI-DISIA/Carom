// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cassert>
#include <ctime>
#include <random>

#include "RandomNumberGenerator.h"

class RandomNumberGenerator {
public:

	RandomNumberGenerator(const RandomNumberGenerator&) = delete;
	RandomNumberGenerator& operator=(RandomNumberGenerator&) = delete;

	RandomNumberGenerator() :
		RandomNumberGenerator(static_cast<unsigned int>(std::time(0))) {
	}

	RandomNumberGenerator(unsigned seed) :
			_gen(seed), _dist(), _ins() {
	}

	inline void Inseminate(unsigned seed) {
		_gen = std::mt19937(seed);
	}

	virtual ~RandomNumberGenerator() {
	}

	inline int nextInt() {
		return _dist(_gen);
	}

	inline float nextFloat() {
		return _ins(_gen);
	}

	// return an integer between low (inclusive) and high (exclusive)
	inline int nextInt(int low, int high) {
		assert(low < high);
		return low + (nextInt() % (high - low));
	}

	inline float nextFloat(float low, float high) {
		assert(low <= high);
		return low + nextFloat() * (high-low);
	}

private:
	std::mt19937 _gen;
	std::uniform_int_distribution<int> _dist;
	std::uniform_real_distribution<float> _ins;
};

