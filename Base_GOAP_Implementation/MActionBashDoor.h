#pragma once
#include "MAction.h"

class MActionBashDoor : public MAction
{
private:
	float _distance = 1.0f;

public:
	MActionBashDoor()
	{
		actCost = 5.0f;
	}

	void CheckPreCons() {}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("Checking Bash Door Pres");
		int factId = state->GetConfidentFactIdx(fct_hasdoorkey);

		if (factId == -1)
			return false;

		return true;
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("Applying Bash Door Post Cons");
		int factId = state.GetConfidentFactIdx(fct_dooropen);

		state._facts[factId].SetDoorOpen(true);

		return state;
	}
};