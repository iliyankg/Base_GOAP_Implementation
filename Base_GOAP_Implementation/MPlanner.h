#pragma once
#include "MWorkingMemory.h"

enum MActionTypes
{
	badaction = -1, 
	act_opendoor,
	num_actions
};

struct MPlannerNode
{
	MWMemory stateAtNode;
	float g;
	float h;
	float f;
	MActionTypes action_edge;
	MWMemory cameFrom;
};

class MPLanner
{
	MPLanner() {}
	~MPLanner() {}

	std::vector<MPlannerNode> openSet;
	std::vector<MPlannerNode> closedSet;

	void PrintPlan() {};

	int CalculateHeuristic(MWMemory& stateFrom, MWMemory& stateTo)
	{
		int counter = 0;

		for (int i = 0; i < stateFrom._facts.size(); ++i)
		{
			if (*stateFrom._facts[i] != *stateTo._facts[i])
				counter++;
		}

		return counter;
	}

	int OpenIdx(MWMemory& state)
	{
		for (int i = 0; i < openSet.size(); ++i)
			if (openSet[i].stateAtNode == state)
				return i;

		return -1;
	}

	int ClosedIdx(MWMemory& state)
	{
		for (int i = 0; i < closedSet.size(); ++i)
			if (closedSet[i].stateAtNode == state)
				return i;

		return -1;
	}

	void Plan(MWMemory& start, MWMemory& goal)
	{
		openSet.clear();
		closedSet.clear();
		
		MPlannerNode tempStart;
		tempStart.stateAtNode = start;
		tempStart.action_edge = badaction;
		tempStart.g = 0;
		tempStart.h = CalculateHeuristic(start, goal);
		openSet.push_back(tempStart);
		
		while (!openSet.empty())
		{
			MPlannerNode current = openSet[0];
			openSet.erase(openSet.begin());
			closedSet.push_back(current);

			if (current.stateAtNode == goal)
			{
				PrintPlan();
				return;
			}
			
			std::vector<MPlannerNode> possibleTransitions;

			for (int i = 0; i < num_actions; ++i)
			{
				//TO DO: ADD PRE-CON CHECK
				
			}
		}
	}

};