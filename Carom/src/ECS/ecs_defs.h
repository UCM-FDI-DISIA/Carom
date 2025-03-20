#pragma once

// Components list - must have at least one element
// TODO completar
#define _CMPS_LIST_ \
	TRANSFORM, \
	RENDER_TEXTURE, \
	RIGIDBODY, \
	SHAPE, \
	WHITEBALLSCORER, \
	COLORBALLSCORER, \
	WALL, \
	TRYCOLLISION, \
	BUTTON, \
	EVENT_ON_COLLISION, \
	STICK_INPUT, \
	TEXT_DISPLAY, \
	FOLLOW, \
	FORCE_AREA, \
	FRICTION, \
	TWEEN, \
	CAMERA, \
	HOLE

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	WHITEBALL, \
	EFFECTBALLS, \
	TABLE, \
	PALO, \
	BACKGROUND, \
	SCORE, \
	SHADOWS, \
	POOL_HOLE, \
	BOSS_MODIFIERS, \
	BOSS_HAND, \
	BOSS_SHADOW, \
	GIMMICK, \
	CAMERA, \
	UI

// Effect list
// TODO completar	
#define _EFFECT_LIST_ \
	NULO, \
	CRISTAL

// Shape list
#define _SHAPE_LIST_ \
	CIRCLE, \
	CAPSULE, \
	POLYGON

// Render layers list
#define _LAYER_LIST_ \
	BACKGROUND, \
	TABLE_SHADOW, \
	SCORE_CONTAINER, \
	TABLE_BACKGOUND, \
	GIMMICK, \
	BALL_SHADOW_ON_TABLE, \
	POOL_HOLE, \
	TABLE_BORDER, \
	EFFECT_BALL, \
	WHITE_BALL, \
	BALL_SHADOW_ON_BALL, \
	SCORE, \
	STICK_SHADOW, \
	STICK, \
	BOSS_HAND, \
	UI
