#include <iostream>

#include "MAgent.h"
#include "MPlanner.h"

MAgent testing; //Testing agent
MPLanner planner; //Planner instance (one per thread)
MWMemory goal; //Goalstate

int main()
{
	testing.agentMemory.CreateFact(fct_enemyhealth, false, 100.0f);
	//testing.agentMemory.CreateFact(fct_haskey, false, 0.0f);

	goal.CreateFact(fct_enemyhealth, true, 0.0f);

	planner.Plan(testing, goal);

	std::cin.get();
	return 0;
}