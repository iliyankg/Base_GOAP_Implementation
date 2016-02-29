#pragma once
#define LOG(toLog) (std::cout << toLog << std::endl);
#include "MWorkingMemory.h"

class MAction
{
public:
	MAction() {}
	~MAction() {}

	float actCost;

	virtual MWMemory* ApplyPostCons(MWMemory* state) = 0;
};