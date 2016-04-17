#pragma once
#include "MAction.h"

class MActionBashDoor : public MAction
{
private:
	float _distance = 1.0f;

public:
	MActionBashDoor(float cost)
	{
		actCost = cost;
	}

	void CheckPreCons() {}

	bool CheckPreCons(MWMemory* state)
	{
		int factId = state->GetConfidentFactIdx(fct_dooropen);

		if (factId != -1)
			return !state->_facts[factId].GetDoorOpen();
		else
			return false;
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