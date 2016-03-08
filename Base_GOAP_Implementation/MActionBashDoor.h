#pragma once
#include "MAction.h"

class MActionBashDoor : public MAction
{
private:
	static const int numPre = 1;
	static const int numPost = 1;


	float _distance = 1.0f;

public:
	MActionBashDoor()
	{
		actCost = 4.0f;
	}

	void CheckPreCons() {}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("Checking Bash Door Pres");
		int factId = state->GetConfidentFactIdx(fct_haskey);

		return true;

		return !state->_facts[factId].GetHasKey();
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("Applying Bash Door Post Cons");
		int factId = state.GetConfidentFactIdx(fct_door);

		state._facts[factId].SetDoorOpen(true);

		return state;
	}
};