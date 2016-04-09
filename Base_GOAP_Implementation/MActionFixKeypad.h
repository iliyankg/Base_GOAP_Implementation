#pragma once
#include "MAction.h"

class MActionFixKeypad : public MAction
{
private:
public:
	MActionFixKeypad(float cost)
	{
		actCost = cost;
	}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("KEYPAD FIX CHECK");
		int keypadFixedId = state->GetConfidentFactIdx(fct_keypadfixed);

		if (keypadFixedId != -1 && state->_facts[keypadFixedId].GetIsKeypadFixed())
			return false;

		if (keypadFixedId == -1)
			return false;

		int toolsId = state->GetConfidentFactIdx(fct_toolsforkeypad);

		if (toolsId != -1)
			return state->_facts[toolsId].GetHasToolsForKeypad();
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("KEYPAD FIX APPLY");
		int factId = state.GetConfidentFactIdx(fct_keypadfixed);

		state._facts[factId].SetIsKeypadFixed(true);

		return state;
	}
};
