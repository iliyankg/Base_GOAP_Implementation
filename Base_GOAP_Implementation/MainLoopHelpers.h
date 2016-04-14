#pragma once
#include <iostream>
#include <conio.h>

#include "MAction.h"
#include "MWorkingMemory.h"
#include "MPlanner.h"

namespace mlh
{
	void RunAction(MActionTypes actType, MWMemory& state, std::vector<MAction*> &acts)
	{
		int idx = state.GetConfidentFactIdx(fct_key);
		FACT_TYPES openType = invalid;
		state._facts[idx].GetKeyType() == fct_hasdoorkey ? openType = fct_hasdoorkey : openType = fct_keyfortoolbox;

		if (dynamic_cast<MActionGetKey*>(acts[actType]))
			acts[actType]->PerformAction(state, openType);
		else
			acts[actType]->PerformAction(state);
	}

	bool GetInput(char* toReturn)
	{
		if (_kbhit())
		{
			*toReturn = _getch();
			return true; 
		}
		return false;
	}
}