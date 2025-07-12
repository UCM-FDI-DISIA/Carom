// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "ecs_defs.h"

// forward declaration of some classes, to be used when we
// just need to know that they exist
class Entity;
class Component;

// we hide the actual type of the entity
using entity_t = Entity*;
using cmpId_t = uint8_t;
using grpId_t = uint8_t;
using effectId_t = uint8_t;
using shapeId_t = uint8_t;
using layerId_t = uint8_t;
using stickId_t = uint8_t;


namespace cmp {
	// list of component identifiers - note that we rely on that the
	// first number is 0 in C/C++ standard
	enum cmpId : cmpId_t {
		_CMPS_LIST_, /* taken from ecs_defs.h */
	
		// do not remove this
		_LAST_CMP_ID
	};
}

namespace grp {
	// list of group identifiers - note that we rely on that the
	// first number is 0 in C/C++ standard
	enum grpId : grpId_t {
		DEFAULT,
		_GRPS_LIST_, /* taken from ../game/ecs_defs */
	
		// do not remove this
		_LAST_GRP_ID
	};
}

namespace effect {
	// list of game object identifiers - note that we rely on that the
	// first number is 0 in C/C++ standard
	enum effectId : effectId_t {
		_EFFECT_LIST_, /* taken from ecs_defs.h */
	
		// do not remove this
		//Tamanyo de la lista completa de efectos (GENERABLE, NON-GENERABLE EFFECTS)
		_LAST_EFFECT_ID
	};
}

//es una clase para esconder un enum que no se deberia usar
class generableEffect{
	enum generableEffectId : effectId_t{
		_GENERABLE_EFFECT_,

		_LAST_GENERABLE_EFFECT_ID
	};
	public:
	static const effectId_t maxGenerableEffect = _LAST_GENERABLE_EFFECT_ID;
};

namespace stick{
	enum stickId : stickId_t{
		_STICK_LIST_, 

		_LAST_STICK_ID
	};
}

namespace shape {
	// list of game object identifiers - note that we rely on that the
	// first number is 0 in C/C++ standard
	enum shapeId : shapeId_t {
		_SHAPE_LIST_, /* taken from ecs_defs.h */
	
		// do not remove this
		_LAST_EFFECT_ID
	};
}


namespace renderLayer {
	enum layerId : layerId_t {
		_LAYER_LIST_, /* taken from ecs_defs.h */
		_LAST_LAYER_ID
	};
}

constexpr cmpId_t maxComponentId = cmp::cmpId::_LAST_CMP_ID;
constexpr grpId_t maxGroupId = grp::grpId::_LAST_GRP_ID;

// a template variable to obtain the component id.
template<typename T>
constexpr cmpId_t cmpId = T::id;

template<typename T>
constexpr effectId_t effId = T::id;

// a macro for component identifier declaration, e.g., __CMPID_DECL__(_TRANSFORM)
// expands to:
//
//   constexpr static cmpId_type id = _TRANSFORM;
//
// could also be
//
//   enum { id = cmp::TRANSFORM }
//
#define __CMPID_DECL__(cId) constexpr static cmpId_t id = cId;

#define __EFFID_DECL__(eId) constexpr static effectId_t id = eId;