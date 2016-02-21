#pragma once
#include <glm.hpp>
#include "MWorkingMemory.h"

class MActionNodes
{
public:
	MActionNodes() 
	{
		preconditions[0] = NULL;
		postconditions = new MWMFact(atnode, e);
	}
	~MActionNodes() {}

	glm::vec3 ApplyActionEffects(glm::vec3& movablepos, glm::vec3& moveto)
	{
		movablepos += glm::normalize(moveto - movablepos) * _distance;
	}
	
	static const int numPre = 1;
	static const int numPost = 1;

	MWMFact* preconditions[numPre];
	MWMFact* postconditions[numPost];

private:
	float _distance = 1.0f;
};