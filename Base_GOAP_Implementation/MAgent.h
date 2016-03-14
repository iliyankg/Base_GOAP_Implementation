#pragma once
#include <glm.hpp>
#include "MAction.h"
#include "MWorkingMemory.h"
#include "MGoalManager.h"

class MAgent
{
public:
	MAgent(glm::vec3 pos, glm::vec3 orient) 
	{
		_position = pos;
		_orientation = orient;
	}
	~MAgent() {}

	glm::vec3 _position;
	glm::vec3 _orientation;

	static const int numAvailableActions = 4;
	MActionTypes agentActions[numAvailableActions] = { act_opendoor, act_getkey, act_bashdoor, act_damageenemy };

	MWMemory agentMemory;
};