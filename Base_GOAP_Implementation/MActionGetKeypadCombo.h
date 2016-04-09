#pragma once
#include "MAction.h"

class MActionGetKeypadCombo : public MAction
{
private:
public: 
	MActionGetKeypadCombo(float cost)
	{
		actCost = cost;
	}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("GET COMBO CHECK");
		int comboId = state->GetConfidentFactIdx(fct_keypadcombonote);

		if (comboId != -1 && state->_facts[comboId].GetKeypadCombo() == 1234)
			return false;

		if (comboId == -1)
			return false;

		return true;
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("COMBO APPLY");
		int factId = state.GetConfidentFactIdx(fct_keypadcombonote);

		state._facts[factId].SetKeypadCombo(1234);

		return state;
	}
};