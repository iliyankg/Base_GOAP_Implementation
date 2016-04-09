#include <iostream>

#include "MAgent.h"
#include "MPlanner.h"

MAgent testing; //Testing agent
MPLanner planner; //Planner instance (one per thread)
MWMemory goal; //Goalstate

int main()
{
	testing.agentMemory.CreateFact(fct_enemyhealth, 100.0f);
	testing.agentMemory.CreateFact(fct_enemyhealth, 100.0f);
	//testing.agentMemory.CreateFact(fct_key, fct_keyfortoolbox);
	//testing.agentMemory.CreateFact(fct_key, fct_hasdoorkey);
	//testing.agentMemory.CreateFact(fct_hasdoorkey, false);
	//testing.agentMemory.CreateFact(fct_dooropen, false);
	//testing.agentMemory.CreateFact(fct_keypadfixed, false);
	//testing.agentMemory.CreateFact(fct_keyfortoolbox, false);
	//testing.agentMemory.CreateFact(fct_toolsforkeypad, false);
	//testing.agentMemory.CreateFact(fct_keypadfixed, false);
	//testing.agentMemory.CreateFact(fct_keypadcombonote, 0);

	goal.CreateFact(fct_enemyhealth, 0.0f);
	//goal.CreateFact(fct_hasdoorkey, true);
	//goal.CreateFact(fct_dooropen, true);
	//goal.CreateFact(fct_keypadfixed, true);
	//goal.CreateFact(fct_keyfortoolbox, true);
	//goal.CreateFact(fct_toolsforkeypad, true);
	//goal.CreateFact(fct_keypadfixed, true);
	//goal.CreateFact(fct_keypadcombonote, 1234);

	planner.Plan(testing, goal);

	std::cin.get();
	return 0;
}