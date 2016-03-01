#pragma once
#include "MActionh.h"

class MActionGetKey : public MAction
{
private:
	static const int numPre = 0;
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

		return !state->_facts[factId]->GetHasKey();
	}

	MWMemory* ApplyPostCons(MWMemory* state)
	{
		LOG("Applying Get Key Post Cons");
		MWMemory* temp = new MWMemory(*state);

		int factId = temp->GetConfidentFactIdx(fct_haskey);

		if (!temp->_facts[factId]->GetHasKey());
		temp->_facts[factId]->SetHasKey(true);

		return temp;
	}
};