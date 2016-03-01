#pragma once
#include "MActionh.h"

class MActionOpenDoor : public MAction
{
private:
	static const int numPre = 1;
	static const int numPost = 1;


	float _distance = 1.0f;

public:
	MActionOpenDoor()
	{
		actCost = 1.0f;
	}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("Checking Open Door Pres");
		int factId = state->GetConfidentFactIdx(fct_haskey);

		return state->_facts[factId]->GetHasKey();
	}

	MWMemory* ApplyPostCons(MWMemory* state)
	{
		LOG("Applying Open Door Post Cons");
		MWMemory* temp = new MWMemory(*state);

		int factId = temp->GetConfidentFactIdx(fct_door);

		if (!temp->_facts[factId]->GetDoorOpen());
			temp->_facts[factId]->SetDoorOpen(true);

		return temp;
	}
};