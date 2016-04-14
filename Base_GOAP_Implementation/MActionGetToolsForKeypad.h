#pragma once
#include "MAction.h"

class MActionGetToolsForKeypad : public MAction
{
private:
public:
	MActionGetToolsForKeypad(float cost)
	{
		actCost = cost;
	}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("GET TOOLS CHECK");
		int repeatCheckId = state->GetConfidentFactIdx(fct_toolsforkeypad);

		if (repeatCheckId != -1 && state->_facts[repeatCheckId].GetHasToolsForKeypad())
			return false;	
		
		int hasKeysForBox = state->GetConfidentFactIdx(fct_keyfortoolbox);
		if (hasKeysForBox != -1)
			return state->_facts[hasKeysForBox].GetHasKeyForToolbox();

		int hasLockpickId = state->GetConfidentFactIdx(fct_lockpickfortoolbox);
		if (hasLockpickId != -1)
			return state->_facts[hasLockpickId].GetHasLockpick();
		
		return false;
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("GET TOOLS APPLY");
		int factId = state.GetConfidentFactIdx(fct_toolsforkeypad);

		state._facts[factId].SetHasToolsForKeypad(true);

		return state;
	}

	void PerformAction(MWMemory &state)
	{
		int factId = state.GetConfidentFactIdx(fct_toolsforkeypad);

		state._facts[factId].SetHasToolsForKeypad(true);

	}

};