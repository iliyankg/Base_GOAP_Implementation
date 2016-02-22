#pragma once
#include <glm.hpp>
#include "MWorkingMemory.h"
#include "MActionOpenDoor.h"

class MAgent
{
public:
	MAgent(glm::vec3 pos, glm::vec3 orient) 
	{
		_position = pos;
		_orientation = orient;

		actions.push_back(new MActionOpenDoor());
	}
	~MAgent() {}

	glm::vec3 _position;
	glm::vec3 _orientation;

	std::vector<MWMemory* (MWMemory*)> PostFuncs;

	std::vector<MAction*> actions;

	MWMemory agentMemory;
};