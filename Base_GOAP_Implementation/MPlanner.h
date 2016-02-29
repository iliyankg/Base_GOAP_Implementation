#pragma once


#include <iostream>

#include "MWorkingMemory.h"
#include "MActionOpenDoor.h"

enum MActionTypes
{
	badaction = -1, 
	act_opendoor,
	num_actions
};

struct MPlannerNode
{
	friend bool operator== (const MPlannerNode& left, const MPlannerNode& right)
	{
		if (left.action_edge == right.action_edge && left.stateAtNode == right.stateAtNode)
			return true;
		else 
			return false;
	}
	friend bool operator!= (const MPlannerNode& left, const MPlannerNode& right)
	{
		return !(left == right);
	}

	MWMemory stateAtNode;
	float g;
	float h;
	float f;
	MActionTypes action_edge;
	MPlannerNode* cameFrom;
};

class MPLanner
{
public:
	MPLanner() 
	{
		LOG("Created Planner")
		allActions.push_back(new MActionOpenDoor());
	}
	~MPLanner() {}

	std::vector<MAction*> allActions;

	void PrintPlan()
	{
		std::cout << "TOP ZOZZLE" << std::endl;
	}

	std::vector<MPlannerNode> openSet;
	std::vector<MPlannerNode> closedSet;

	void Plan(MWMemory& start, MWMemory& goal)
	{
		LOG("Starting Planning");

		bool isRouteFound = false;

		openSet.clear();
		closedSet.clear();
		
		MPlannerNode tempStart;
		tempStart.stateAtNode = start;
		tempStart.action_edge = badaction;
		tempStart.g = 0;
		tempStart.h = CalculateHeuristic(start, goal);
		openSet.push_back(tempStart);
		
		do
		{
			MPlannerNode current = openSet[0];
			openSet.erase(openSet.begin());
			closedSet.push_back(current);

			if (current.stateAtNode == goal)
			{
				LOG("Plan Found");
				isRouteFound = true;
				PrintPlan();
				return;
			}

			if (!isRouteFound)
			{
				for (int i = 0; i < num_actions; ++i)
				{
					//TO DO: ADD PRE-CON CHECK
					MPlannerNode tempNode;

					tempNode.stateAtNode = *allActions[i]->ApplyPostCons(&current.stateAtNode);
					tempNode.action_edge = (MActionTypes)i;
					tempNode.cameFrom = &current;

					tempNode.g = allActions[i]->actCost + current.g;
					tempNode.h = CalculateHeuristic(tempNode.stateAtNode, goal);
					tempNode.f = tempNode.g + tempNode.h;

					//Check if in closed
					if (!IsInClosed(tempNode))
					{
						LOG("Not In Closed");

						int idx;
						if (!IsInOpen(tempNode, idx))
						{
							LOG("Not In Opened");
							OrderedInsertion(openSet, tempNode);
						}
						else
						{
							LOG("In Opened");
							if (current.f + CalculateHeuristic(current.stateAtNode, tempNode.stateAtNode) < openSet[idx].f)
							{
								openSet[idx].g = current.g + CalculateHeuristic(current.stateAtNode, openSet[idx].stateAtNode);
								openSet[idx].f = openSet[idx].g + openSet[idx].h;
								openSet[idx].cameFrom = &current;
							}
						}
					}
				}
			}
		} while (!openSet.empty() && !isRouteFound);
	}

private:
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

	float CalculateHeuristic(MWMemory& stateFrom, MWMemory& stateTo)
	{
		float counter = 0;

		for (int i = 0; i < stateFrom._facts.size(); ++i)
		{
			if (*stateFrom._facts[i] != *stateTo._facts[i])
				counter++;
		}

		return counter;
	}

	void OrderedInsertion(std::vector<MPlannerNode> &vec, MPlannerNode toInsert)
	{
		int counter = 0;

		for (int i = 0; i < vec.size(); ++i)
		{
			if (vec[i].f < toInsert.f)
				counter++;
		}
		vec.insert(vec.begin() + counter, toInsert);
	}
	
	bool IsInClosed(MPlannerNode toCheck)
	{
		for (int i = 0; i < closedSet.size(); ++i)
		{
			if (closedSet[i] == toCheck)
				return true;
		}
		return false;
	}
	bool IsInOpen(MPlannerNode toCheck, int &openIdx)
	{
		for (int i = 0; i < openSet.size(); ++i)
		{
			if (openSet[i] == toCheck)
			{
				openIdx = i;
				return true;
			}
		}
		openIdx = -1;
		return false;
	}
};