#pragma once
#include "MAction.h"

class MActionOpenDoor : public MAction
{
private:
	float _distance = 1.0f;

public:
	MActionOpenDoor(float cost)
	{
		actCost = cost;
	}

	bool CheckPreCons(MWMemory* state)
	{
		int factId = state->GetConfidentFactIdx(fct_dooropen);

		if (factId != -1 && state->_facts[factId].GetDoorOpen())
			return false;

		//Open With Key
		int hasKeyId = state->GetConfidentFactIdx(fct_hasdoorkey);

		if (hasKeyId != -1 && state->_facts[hasKeyId].GetHasDoorKey())
			return true;

		//Open With Key Combo
		int keyPadWorksId = state->GetConfidentFactIdx(fct_keypadfixed);
		int hasKeyComboId = state->GetConfidentFactIdx(fct_keypadcombonote);

		if (keyPadWorksId == -1 || hasKeyComboId == -1)
			return false;
		else
			if(state->_facts[hasKeyComboId].GetKeypadCombo() == 1234)
				return state->_facts[keyPadWorksId].GetIsKeypadFixed();
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		int factId = state.GetConfidentFactIdx(fct_dooropen);

		state._facts[factId].SetDoorOpen(true);

		return state;
	}

	void PerformAction(MWMemory &state)
	{
		int factId = state.GetConfidentFactIdx(fct_dooropen);

		state._facts[factId].SetDoorOpen(true);
	}
};