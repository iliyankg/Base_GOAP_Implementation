#pragma once
#include "MAction.h"

class MActionGetKey : public MAction
{
private:
	static const int numPre = 1;
	static const int numPost = 1;


	float _distance = 1.0f;

public:
	MActionGetKey()
	{
		actCost = 1.0f;
	}

	void CheckPreCons() {}
	
	bool CheckPreCons(MWMemory* state) 
	{
		LOG("Checking Get Key Pres");
		int factId = state->GetConfidentFactIdx(fct_haskey);

		return !state->_facts[factId].GetHasKey();
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("Applying Get Key Post Cons");
		int factId = state.GetConfidentFactIdx(fct_haskey);
		
		if (factId == -1)
			state.CreateFact(fct_haskey, true);
		else
			state._facts[factId].SetHasKey(true);

		return state;
	}
};