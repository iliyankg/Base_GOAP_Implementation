#pragma once
#include "MAction.h"

class MActionOpenDoor : public MAction
{
private:
	static const int numPre = 1;
	static const int numPost = 1;


	float _distance = 1.0f;

public:
	MActionOpenDoor()
	{
		actCost = 2.0f;
	}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("Checking Open Door Pres");
		int factId = state->GetConfidentFactIdx(fct_haskey);

		return state->_facts[factId].GetHasKey();
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("Applying Open Door Post Cons");
		int factId = state.GetConfidentFactIdx(fct_door);

		state._facts[factId].SetDoorOpen(true);

		return state;
	}
};