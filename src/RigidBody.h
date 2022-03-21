#pragma once
#ifndef __RIGID_BODY__
#define __RIGID_BODY__
#include <glm/vec2.hpp>

struct RigidBody
{
	friend class GameObjec;

	float mass;
	
	glm::vec2 velocity;
	glm::vec2 acceleration;
	float maxVelocity;

	bool hasCollider;
	bool isColliding;
};
#endif /* defined (__RIGID_BODY__) */