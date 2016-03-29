#pragma once
#include "MAction.h"

class MActionGetKey : public MAction
{
private:
	float _distance = 1.0f;

public:
	MActionGetKey()
	{
		actCost = 10.0f;
	}

	void CheckPreCons() {}
	
	bool CheckPreCons(MWMemory* state) 
	{
		LOG("Checking Get Key Pres");
		int factId = state->GetConfidentFactIdx(fct_hasdoorkey);

		if (factId == -1)
			return false;

		return !state->_facts[factId].GetHasDoorKey();
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("Applying Get Key Post Cons");
		int factId = state.GetConfidentFactIdx(fct_hasdoorkey);
		
		if (factId == -1)
			state.CreateFact(fct_hasdoorkey, true);
		else
			state._facts[factId].SetHasDoorKey(true);

		return state;
	}
};