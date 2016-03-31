#pragma once
#include <glm.hpp>
#include "MAction.h"
#include "MWorkingMemory.h"
#include "MGoalManager.h"

class MAgent
{
public:
	MAgent()
	{

	}
	~MAgent() {}

	MActionTypes currentAction = badaction;
	static const int numAvailableActions = 4; 
	MActionTypes agentActions[numAvailableActions] = { 
		act_opendoor,
		act_getdoorkey,
		act_bashdoor,
		act_damageenemy };
	
	MGoalTypes currentGoal = badgoal;
	static const int numAvailableGoals = 2; 
	MGoalTypes agentGoals[numAvailableGoals] = { 
		goal_killenemy,
		goal_opendoor };
	
	std::vector<MActionTypes> actionsForCurrentPlan;

	MGoalManager goalManager;
	MWMemory agentMemory;
};