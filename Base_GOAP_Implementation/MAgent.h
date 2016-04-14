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
	static const int numAvailableActions = 7; 
	MActionTypes agentActions[numAvailableActions] = { 
		act_opendoor,
		act_getdoorkey,
		act_bashdoor,
		act_damageenemy,
		act_fixkeypad,
		act_getkeypadcode,
		act_gettoolsforkeypad
	};
	
	MGoalTypes currentGoal = badgoal;
	static const int numAvailableGoals = 3; 
	MGoalTypes agentGoals[numAvailableGoals] = { 
		goal_killenemy,
		goal_opendoorkey,
		goal_opendoorcombo};
	
	std::vector<MActionTypes> actionsForCurrentPlan;

	MGoalManager goalManager;
	MWMemory agentMemory;
	MWMemory goalMemory;
};