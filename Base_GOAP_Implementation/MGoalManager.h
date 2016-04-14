#pragma once
#include <vector>
#include "MWorkingMemory.h"

enum MGoalTypes
{
	badgoal = -1,
	goal_opendoorkey,
	goal_opendoorcombo,
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

	MWMemory GetNewGoal(MWMemory& agenMemory, int numOfGoals, MGoalTypes availableGoals[], MWMemory& currentGoalMemory)
	{
		MWMemory toReturn;
		switch (CalculateGoalPriorities(agenMemory, numOfGoals, availableGoals))
		{
		case goal_opendoorkey:
			toReturn.CreateFact(fct_dooropen, true);
			break;
		case goal_opendoorcombo:
			toReturn.CreateFact(fct_dooropen, true);
			toReturn.CreateFact(fct_keypadfixed, true);
			break;
		case goal_killenemy:
			toReturn.CreateFact(fct_enemyhealth, 0.0f);
			break;
		default:
			break;
		}

		return toReturn;
	}
private:
	MGoalTypes CalculateGoalPriorities(MWMemory& agentMemory, int numOfGoals, MGoalTypes available_goals[])
	{
		int idx = agentMemory.GetConfidentFactIdx(fct_enemyhealth);

		if (idx != -1)
			return goal_killenemy;

		std::vector<int> keyIds = agentMemory.GetAllFactsOfType(fct_key);
		if (keyIds[0] == -1)
			return goal_opendoorkey;
		if (keyIds.size() == 1)
		{
			switch (agentMemory._facts[keyIds[0]].GetKeyType())
			{
			case fct_hasdoorkey:
				return goal_opendoorkey;
				break;
			case fct_keyfortoolbox:
				return goal_opendoorcombo;
				break;
			}
		}
		else if (keyIds.size() == 2)
			return goal_opendoorkey;
	}


};