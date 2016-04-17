#include "MAgent.h"
#include "MPlanner.h"
#include "MRoomManager.h"
#include "MainLoopHelpers.h"

MAgent testingAgent; //Testing agent
MAgent testingAgentTwo;
MAgent testingAgentThree;
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
		{
			testingAgent.agentMemory = roomManager.GetRoomKnowledge();
			testingAgentTwo.agentMemory = roomManager.GetRoomKnowledge();
			testingAgentThree.agentMemory = roomManager.GetRoomKnowledge();
		}
			

		mlh::RunActionInPlan(testingAgent, planner.allActions);
		mlh::RunActionInPlan(testingAgentTwo, planner.allActions);
		

		if (testingAgent.actionsForCurrentPlan.empty())
		{
			mlh::chrn_timepoint tpOne = mlh::chrn_hrc::now();
			//=================PLANNING============//
			//testingAgent.actionsForCurrentPlan = planner.Plan(testingAgent);
			//std::future< std::vector<MActionTypes> > testingFuture = std::async(std::launch::async, mlh::WorkerFunction, planner, testingAgent);
			//testingAgent.actionsForCurrentPlan = testingFuture.get();
			
			std::thread testThread(&mlh::SecondaryWorkerFunction, planner, testingAgent, std::ref(testingAgent.actionsForCurrentPlan));
			std::thread testThreadTwo(&mlh::SecondaryWorkerFunction, planner, testingAgentTwo, std::ref(testingAgentTwo.actionsForCurrentPlan));
			std::thread testThreadThree(&mlh::SecondaryWorkerFunction, planner, testingAgentThree, std::ref(testingAgentThree.actionsForCurrentPlan));
	
			testThread.join();
			testThreadTwo.join();
			testThreadThree.join();
			//=================PLANNING============//
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