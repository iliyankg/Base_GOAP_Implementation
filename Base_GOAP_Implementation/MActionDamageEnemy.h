#pragma once
#include "MAction.h"

class MActionDamageEnemy : public MAction
{
private:
	float _distance = 1.0f;

public:
	MActionDamageEnemy(float cost)
	{
		actCost = cost;
	}

	bool CheckPreCons(MWMemory* state)
	{
		int factId = state->GetConfidentFactIdx(fct_enemyhealth);

		if (factId == -1)
			return false;

		return state->_facts[factId].GetEnemyHealth() > 0;
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		int factId = state.GetConfidentFactIdx(fct_enemyhealth);

		state._facts[factId].SetEnemyHealth(state._facts[factId].GetEnemyHealth() - 10.0f);

		if (state._facts[factId].GetEnemyHealth() <= 0.0f)
			state._facts[factId].SetConfidance(0.0f);

		return state;
	}

	void PerformAction(MWMemory &state)
	{
		int factId = state.GetConfidentFactIdx(fct_enemyhealth);

		state._facts[factId].SetEnemyHealth(state._facts[factId].GetEnemyHealth() - 10.0f);

		if (state._facts[factId].GetEnemyHealth() <= 0.0f)
			state._facts.erase(state._facts.begin() + factId);

	}
};