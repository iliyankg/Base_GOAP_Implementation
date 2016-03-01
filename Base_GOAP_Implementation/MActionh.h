#pragma once
#include "MWorkingMemory.h"

enum MActionTypes
{
	badaction = -1,
	act_opendoor,
	act_getkey,
	num_actions
};

class MAction
{
public:
	MAction() {}
	~MAction() {}

	float actCost;

	virtual bool CheckPreCons(MWMemory* state) = 0;
	virtual MWMemory* ApplyPostCons(MWMemory* state) = 0;
};