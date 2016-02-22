#pragma once
#include <glm.hpp>
#include "MWorkingMemory.h"

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

	MWMemory agentMemory;
};