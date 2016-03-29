#pragma once
#include <vector>
#include "MWorkingMemory.h"

enum MGoalTypes
{
	badgoal = -1,
	goal_opendoor,
	goal_killenemy,
	num_goals
};

enum MGoalFlatPriorities
{
	badpriority = -1,
	priority_opendoor = 100,
	priority_killenemy = 50,
	num_priorities
};

class MGoalManager
{
public:
	MGoalManager() {}
	~MGoalManager() {}

	void CalculateGoalPriorities(std::vector<MWMemory*> agentMemorie, int numOfGoals, MGoalTypes available_goals[])
	{
		 
	}

private:
};