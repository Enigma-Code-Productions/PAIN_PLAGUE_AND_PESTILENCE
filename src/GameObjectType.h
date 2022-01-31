#pragma once
#ifndef __GAME_OBJECT_TYPE__
#define __GAME_OBJECT_TYPE__
enum GameObjectType
{
	NONE = -1,
	AGENT,
	OBSTACLE,
	TARGET,
	ENEMY,
	PLAYER,
	UI_ELEMENT,
	START_BUTTON,
	RESTART_BUTTON,
	BACK_BUTTON,
	NEXT_BUTTON,
	MELEE_WEAPON,
	RANGED_WEAPON,
	PATH_NODE,
	NUM_OF_TYPES
};
#endif /* defined (__GAME_OBJECT_TYPE__) */