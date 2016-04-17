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
	char exitKey = ' ';

	std::ofstream file;
	file.open("output.txt");

	int counter = 0;

	while (counter != 10000/*exitKey != 'q'*/)
	{
		++counter;
		mlh::GetInput(&exitKey);

		if (testingAgent.actionsForCurrentPlan.empty() || testingAgent.agentMemory._facts[testingAgent.agentMemory.GetConfidentFactIdx(fct_dooropen)].GetDoorOpen())
			testingAgent.agentMemory = roomManager.GetRoomKnowledge();

		mlh::RunActionInPlan(testingAgent, planner.allActions);

		if (testingAgent.actionsForCurrentPlan.empty())
		{
			mlh::chrn_timepoint tpOne = mlh::chrn_hrc::now();
			
			testingAgent.actionsForCurrentPlan = planner.Plan(testingAgent);
		
			mlh::chrn_timepoint tpTwo = mlh::chrn_hrc::now();
			auto time = std::chrono::duration_cast<std::chrono::microseconds>(tpTwo - tpOne).count();

			int planSize = testingAgent.actionsForCurrentPlan.size();
			if (planSize > 8)
				file << time << ",";
			else if (planSize > 3)
				file  << time << "\n";
			else if (planSize >= 2)
				file << "," << time <<"\n";

			mlh::LogExecTime("Time - Main Loop", tpOne, tpTwo);
		}
			
		
	}

	file.close();

	LOG("END");
	std::cin.get();
	return 0;
}