#include <iostream>

#include "MAgent.h"
#include "MPlanner.h"

MAgent testing(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 0.0, 0.0));
MAgent testingTwo(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 0.0, 0.0));

MPLanner planner;

bool a(MWMemory& left, MWMemory& right)
{
	for (int i = 0; i < left._facts.size(); ++i)
	{
		if (left._facts[i] != right._facts[i])
			return false;
	}
	return true;
}

int main()
{
	testing.agentMemory.CreateFact(fct_door, false, 100.0f);
	testing.agentMemory.CreateFact(fct_haskey, false, 0.0f);

	MWMemory goal; 
	goal.CreateFact(fct_door, true, 0.0f);

	planner.Plan(testing, goal);

	std::cin.get();
	return 0;
}