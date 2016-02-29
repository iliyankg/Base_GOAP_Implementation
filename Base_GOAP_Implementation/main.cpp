#include <iostream>

#include "MAgent.h"
#include "MPlanner.h"

MAgent testing(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 0.0, 0.0));
MPLanner planner;

int main()
{
	testing.agentMemory.CreateFact(fct_door, false);

	MWMemory goal; 
	goal.CreateFact(fct_door, true);

	planner.Plan(testing.agentMemory, goal);

	std::cin.get();
	return 0;
}