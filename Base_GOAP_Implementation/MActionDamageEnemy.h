#pragma once
#include "MAction.h"

class MActionDamageEnemy : public MAction
{
private:
	float _distance = 1.0f;

public:
	MActionDamageEnemy()
	{
		actCost = 2.0f;
	}

	bool CheckPreCons(MWMemory* state)
	{
		LOG("Checking Damage Enemy Pres");
		int factId = state->GetConfidentFactIdx(fct_enemyhealth);

		if (factId == -1)
			return false;

		return state->_facts[factId].GetEnemyHealth() > 0;
	}

	MWMemory ApplyPostCons(MWMemory state)
	{
		LOG("Applying Damage Enemy Post Cons");
		int factId = state.GetConfidentFactIdx(fct_enemyhealth);

		state._facts[factId].SetEnemyHealth(state._facts[factId].GetEnemyHealth() - 10.0f);

		return state;
	}
};