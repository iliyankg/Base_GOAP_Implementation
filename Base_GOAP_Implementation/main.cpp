#include "MAgent.h"
#include "MPlanner.h"
#include "MRoomManager.h"
#include "MainLoopHelpers.h"

MAgent testingAgent; //Testing agent
MRoomManager roomManager;
MPLanner planner; //Planner instance (one per thread)
MWMemory goal; //Goalstate


int main()
{
	//testingAgent.agentMemory = roomManager.GetRoomKnowledge();

	//std::vector<MActionTypes> temp = planner.Plan(testingAgent);

	//for (int i = 1; i < temp.size(); ++i)
	//{
	//	mlh::RunAction(temp[i], testingAgent.agentMemory, planner.allActions);
	//}
	
	//planner.Plan(testingAgent);

	//std::cin.get();

	char exitKey = ' ';

	while (exitKey != 'q')
	{
		mlh::GetInput(&exitKey);
		LOG("LOGIC");
	}
	LOG("END");
	std::cin.get();
	return 0;
}