#include <iostream>

#include "MAgent.h"

MAgent testing(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 0.0, 0.0));


int main()
{
	testing.agentMemory.CreateFact(fct_door, false);

	std::cin.get();
	return 0;
}