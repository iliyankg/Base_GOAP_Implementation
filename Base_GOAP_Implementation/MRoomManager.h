#pragma once
#include <time.h>
#include <random>
#include "MWorkingMemory.h"

//testing.agentMemory.CreateFact(fct_enemyhealth, 100.0f); 
//testing.agentMemory.CreateFact(fct_key, fct_keyfortoolbox); 
//testing.agentMemory.CreateFact(fct_key, fct_hasdoorkey); 
//testing.agentMemory.CreateFact(fct_hasdoorkey, false); 
//testing.agentMemory.CreateFact(fct_dooropen, false); 
//testing.agentMemory.CreateFact(fct_keypadfixed, false); 
//testing.agentMemory.CreateFact(fct_keyfortoolbox, false); 
//testing.agentMemory.CreateFact(fct_toolsforkeypad, false); 
//testing.agentMemory.CreateFact(fct_keypadcombonote, 0); 


class MRoomManager
{
public:
	MRoomManager() { srand(time(NULL)); }
	~MRoomManager() {}

	MWMemory GetRoomKnowledge()
	{
		MWMemory toReturn;
		AddMinFacts(toReturn);

		AddEnemies(toReturn, GetRandomInRange(1, 1));
		GetRandomInRange(1, 100) > 60 ? AddKeyPath(toReturn) : AddKeypadPath(toReturn);

		return toReturn;		
	}

private:
	int GetRandomInRange(int low, int high)
	{
		return rand() % high + low;
	}

	void AddMinFacts(MWMemory& addTo)
	{
		addTo.CreateFact(fct_dooropen, false);
	}
	void AddKeyPath(MWMemory& addTo)
	{
		addTo.CreateFact(fct_key, fct_hasdoorkey);
		addTo.CreateFact(fct_hasdoorkey, false);
	}
	void AddKeypadPath(MWMemory& addTo)
	{
		addTo.CreateFact(fct_key, fct_keyfortoolbox);
		addTo.CreateFact(fct_keyfortoolbox, false);
		addTo.CreateFact(fct_keypadcombonote, 0);
		addTo.CreateFact(fct_keypadfixed, false);
		addTo.CreateFact(fct_toolsforkeypad, false);

	}
	void AddEnemies(MWMemory& addTo, int numToAdd)
	{
		for (int i = 0; i < numToAdd; i++)
		{
			addTo.CreateFact(fct_enemyhealth, 100.0f);
		}
	}
};