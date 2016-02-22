#pragma once
#include <glm.hpp>
#include "MWorkingMemory.h"


class MActionOpenDoor
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

	MWMFact* ApplyPostCons(MWMFact* fact)
	{
		MWMFact* temp = new MWMFact(*fact);

		if (!temp->GetDoorOpen())
			temp->SetDoorOpen(true);

		return temp;
	}
};