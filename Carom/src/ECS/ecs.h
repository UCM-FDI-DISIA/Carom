// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "ecs_defs.h"

// TODO: no completo
namespace ecs {

// forward declaration of some classes, to be used when we
// just need to know that they exist
class Manager;
class Entity;
class Component;

// we hide the actual type of the entity
using entity_t = Entity*;
using cmpId_t = uint8_t;
using objId_t = uint8_t;


namespace cmp {
	// list of component identifiers - note that we rely on that the
	// first number is 0 in C/C++ standard
	enum cmpId : cmpId_t {
		_CMPS_LIST_, /* taken from ecs_defs.h */
	
		// do not remove this
		_LAST_CMP_ID
	};
}

namespace obj {
	// list of game object identifiers - note that we rely on that the
	// first number is 0 in C/C++ standard
	enum objId : objId_t {
		_OBJ_LIST_, /* taken from ecs_defs.h */
	
		// do not remove this
		_LAST_OBJ_ID
	};
}

constexpr cmpId_t maxComponentId = cmp::cmpId::_LAST_CMP_ID;

// a template variable to obtain the component id.
template<typename T>
constexpr cmpId_t cmpId = T::id;

// a macro for component identifier declaration, e.g., __CMPID_DECL__(ecs::_TRANSFORM)
// expands to:
//
//   constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;
//
// could also be
//
//   enum { id = ecs::cmp::TRANSFORM }
//
#define __CMPID_DECL__(cId) constexpr static ecs::cmpId_t id = cId;

} // end of namespace

