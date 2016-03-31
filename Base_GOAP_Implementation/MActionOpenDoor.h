#pragma once
#include "MAction.h"

class MActionOpenDoor : public MAction
{
private:
	float _distance = 1.0f;

public:
	MActionOpenDoor()
	{
		actCost = 2.0f;
	}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("OPEN DOOR CHECK");
		//Open With Key
		int hasKeyId = state->GetConfidentFactIdx(fct_hasdoorkey);

		if (hasKeyId != -1)
			return state->_facts[hasKeyId].GetHasDoorKey();

		//Open With Key Combo
		int keyPadWorksId = state->GetConfidentFactIdx(fct_keypadfixed);
		int hasKeyComboId = state->GetConfidentFactIdx(fct_keypadcombonote);

		if (keyPadWorksId == -1 || hasKeyComboId == -1)
			return false;
		else
			return state->_facts[keyPadWorksId].GetIsKeypadFixed();
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("OPEN DOOR APPLY");
		int factId = state.GetConfidentFactIdx(fct_dooropen);

		state._facts[factId].SetDoorOpen(true);

		return state;
	}
};