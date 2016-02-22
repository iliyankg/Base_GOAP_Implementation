#pragma once
#include <glm.hpp>
#include "MWorkingMemory.h"

class MAction
{
public:
	MAction() {}
	~MAction() {}

	virtual MWMemory* ApplyPostCons(MWMemory* state) = 0;
};

class MActionOpenDoor : public MAction
{
private:
	static const int numPre = 1;
	static const int numPost = 1;


	float _distance = 1.0f;

public:
	MActionOpenDoor()
	{		
	}

	void CheckPreCons() {}

	MWMemory* ApplyPostCons(MWMemory* state)
	{
		MWMemory* temp = new MWMemory(*state);

		int doorFactId = temp->GetConfidentFactIdx(fct_door);

		if (!temp->_facts[doorFactId]->GetDoorOpen());
			temp->_facts[doorFactId]->SetDoorOpen(true);

		return temp;
	}
};