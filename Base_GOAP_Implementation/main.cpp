#include <iostream>

#include "MAgent.h"
#include "MPlanner.h"

MAgent testing; //Testing agent
MPLanner planner; //Planner instance (one per thread)
MWMemory goal; //Goalstate

int main()
{
	//testing.agentMemory.CreateFact(fct_enemyhealth, 100.0f);
	testing.agentMemory.CreateFact(fct_key, fct_hasdoorkey);
	testing.agentMemory.CreateFact(fct_dooropen, false);
	testing.agentMemory.CreateFact(fct_hasdoorkey, false);

	goal.CreateFact(fct_dooropen, true);

	planner.Plan(testing, goal);

	std::cin.get();
	return 0;
}