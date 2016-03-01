#pragma once
#include "MWorkingMemory.h"

class MAction
{
public:
	MAction() {}
	~MAction() {}

	float actCost;

	virtual bool CheckPreCons(MWMemory* state) = 0;
	virtual MWMemory* ApplyPostCons(MWMemory* state) = 0;
};