#pragma once
#include "MWorkingMemory.h"
#include "MAgent.h"

enum MGoalTypes
{
	badgoal = -1,
	goal_opendoor,
	goal_killenemy,
	num_goals
};

class MGoalManager
{
public:
	MGoalManager() {}
	~MGoalManager() {}

	//void CalculateGoalPriorities(MAgent& agent)
	//{
	//	 
	//}

private:
};