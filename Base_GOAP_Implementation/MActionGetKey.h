#pragma once
#include "MAction.h"

#include <vector>

class MActionGetKey : public MAction
{
private:
	float _distance = 1.0f;

public:
	MActionGetKey(float cost)
	{
		actCost = cost;
	}
	
	bool CheckPreCons(MWMemory* state, FACT_TYPES keyType) 
	{
		LOG("GET KEY CHECK");
		int keyTypeId = state->GetConfidentFactIdx(keyType);

		if (keyTypeId != -1)
		{
			switch (keyType)
			{
			case fct_hasdoorkey:
				if (state->_facts[keyTypeId].GetHasDoorKey())
					return false;
				break;
			case fct_keyfortoolbox:
				if (state->_facts[keyTypeId].GetHasKeyForToolbox())
					return false;
				break;
			default:
				break;
			}
		}	

		std::vector<int> factIds = state->GetAllFactsOfType(fct_key);

		if (factIds[0] == -1)
			return false;

		for (int i = 0; i < factIds.size(); ++i)
		{
			if (state->_facts[factIds[i]].GetKeyType() == keyType)
				return true;
		}
		return false;
	}

	MWMemory ApplyPostCons(MWMemory state, FACT_TYPES keyType)
	{
		LOG("GET KEY APPLY");
		std::vector<int> factIds = state.GetAllFactsOfType(fct_key);

		int actualId = -1;

		for (int i = 0; i < factIds.size(); ++i)
		{
			if (state._facts[factIds[i]].GetKeyType() == keyType)
				actualId = factIds[i];
		}

		int tempFactId = -1;

		switch (keyType)
		{
		case fct_hasdoorkey:
			state._facts.erase(state._facts.begin() + actualId);
			tempFactId = state.GetConfidentFactIdx(fct_hasdoorkey);

			if (tempFactId == -1)
				state.CreateFact(fct_hasdoorkey, true);
			else
				state._facts[tempFactId].SetHasDoorKey(true);
			break;
		case fct_keyfortoolbox:
			state._facts.erase(state._facts.begin() + actualId);
			tempFactId = state.GetConfidentFactIdx(fct_keyfortoolbox);

			if (tempFactId == -1)
				state.CreateFact(fct_keyfortoolbox, true);
			else
				state._facts[tempFactId].SetHasKeyForToolbox(true);
			break;
		default:
			break;
		}

		return state;


		//LOG("Applying Get Key Post Cons");
		//int factId = state.GetConfidentFactIdx(fct_hasdoorkey);
		//
		//if (factId == -1)
		//	state.CreateFact(fct_hasdoorkey, true);
		//else
		//	state._facts[factId].SetHasDoorKey(true);

		//return state;
	}
	
	void PerformAction(MWMemory &state, FACT_TYPES keyType)
	{
		std::vector<int> factIds = state.GetAllFactsOfType(fct_key);

		int actualId = -1;

		for (int i = 0; i < factIds.size(); ++i)
		{
			if (state._facts[factIds[i]].GetKeyType() == keyType)
				actualId = factIds[i];
		}

		int tempFactId = -1;

		switch (keyType)
		{
		case fct_hasdoorkey:
			state._facts.erase(state._facts.begin() + actualId);
			tempFactId = state.GetConfidentFactIdx(fct_hasdoorkey);

			if (tempFactId == -1)
				state.CreateFact(fct_hasdoorkey, true);
			else
				state._facts[tempFactId].SetHasDoorKey(true);
			break;
		case fct_keyfortoolbox:
			state._facts.erase(state._facts.begin() + actualId);
			tempFactId = state.GetConfidentFactIdx(fct_keyfortoolbox);

			if (tempFactId == -1)
				state.CreateFact(fct_keyfortoolbox, true);
			else
				state._facts[tempFactId].SetHasKeyForToolbox(true);
			break;
		default:
			break;
		}
	}
};