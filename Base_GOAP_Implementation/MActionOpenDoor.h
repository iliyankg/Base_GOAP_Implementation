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
		LOG("Checking Open Door Pres");
		int factId = state->GetConfidentFactIdx(fct_hasdoorkey);

		if (factId == -1)
			return false;

		return state->_facts[factId].GetHasDoorKey();
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("Applying Open Door Post Cons");
		int factId = state.GetConfidentFactIdx(fct_dooropen);

		state._facts[factId].SetDoorOpen(true);

		return state;
	}
};