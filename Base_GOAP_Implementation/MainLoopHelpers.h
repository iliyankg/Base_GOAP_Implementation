#pragma once
#include <iostream>
#include <conio.h>
#include <chrono>
#include <fstream>

#include "MAction.h"
#include "MWorkingMemory.h"
#include "MPlanner.h"



namespace mlh
{
	typedef std::chrono::high_resolution_clock chrn_hrc;
	typedef std::chrono::high_resolution_clock::time_point chrn_timepoint;
	
	void RunActionInPlan(MAgent& agent, std::vector<MAction*> &acts)
	{
		if (agent.actionsForCurrentPlan.empty())
			return;

		LOG("DID AN ACTION");

		MActionTypes actType = agent.actionsForCurrentPlan[0];

		int idx = agent.agentMemory.GetConfidentFactIdx(fct_key);
		FACT_TYPES openType = invalid;
		agent.agentMemory._facts[idx].GetKeyType() == fct_hasdoorkey ? openType = fct_hasdoorkey : openType = fct_keyfortoolbox;

		if (dynamic_cast<MActionGetKey*>(acts[actType]))
			acts[actType]->PerformAction(agent.agentMemory, openType);
		else
			acts[actType]->PerformAction(agent.agentMemory);

		agent.actionsForCurrentPlan.erase(agent.actionsForCurrentPlan.begin());
	}

	bool GetInput(char* toReturn)
	{
		if (_kbhit())
		{
			*toReturn = _getch();
			return true; 
		}
		return false;
	}

	void LogExecTime(char* label, chrn_timepoint tOne, chrn_timepoint tTwo)
	{
		auto time = std::chrono::duration_cast<std::chrono::microseconds>(tTwo - tOne).count();

		LOG(label << ": " << time);
	}
}