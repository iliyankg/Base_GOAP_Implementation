/** @file MAction.h
*   @brief Contains the MPlannerNode class; MPlanner class;
* 
*	The planner uses A Star pathfinding to run through the possible world states
*	reachable via the potential actions. 
*
*  @author Iliyan Georgiev
*  @bug No known bugs.
*/

#pragma once
#include <iostream>

#include "MWorkingMemory.h"
#include "MActionOpenDoor.h"
#include "MActionGetKey.h"

struct MPlannerNode
{
	//Operator overloads
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

	MWMemory stateAtNode;		//World state at node.
	float g;					//Traverse cost so far
	float h;					//Huristic at node.
	float f;					//G + H cost 
	MActionTypes action_edge;	//Action used to get to this node.
	MPlannerNode* cameFrom;		//Node arived from
};

class MPLanner
{
public:
	MPLanner() 
	{
		LOG("Created Planner")
		allActions.push_back(new MActionOpenDoor());
		allActions.push_back(new MActionGetKey());
	}
	~MPLanner() {}
	
	//All possible actions
	std::vector<MAction*> allActions;

	/** @brief Prints the final plan
	*
	* @return Void
	*/
	void PrintPlan()
	{
		std::cout << "TOP ZOZZLE" << std::endl;
	}

	
	std::vector<MPlannerNode> openSet;		//Open set at for A Star
	std::vector<MPlannerNode> closedSet;	//Closed  set for A Star



	/** @brief Creates a set of actions to go from the start to the goal state.
	*
	* Uses A Star to go through the graph of world states and come up with a set of actions 
	* that satisfy the current goal state. 
	*
	* @param start Start world state.
	* @param goal Goal World state.
	* @return void
	*/
	void Plan(MWMemory& start, MWMemory& goal)
	{
		LOG("Starting Planning");

		bool isRouteFound = false;

		openSet.clear();
		closedSet.clear();
		
		MPlannerNode tempStart;
		tempStart.stateAtNode = start;
		tempStart.action_edge = badaction;
		tempStart.g = 10000.0f;
		tempStart.h = CalculateHeuristic(start, goal);
		tempStart.f = tempStart.h + tempStart.g;
		openSet.push_back(tempStart);
		
		do
		{
			MPlannerNode* current = new MPlannerNode(openSet[0]);
			openSet.erase(openSet.begin());
			closedSet.push_back(*current);

			if (current->stateAtNode == goal)
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
					//Precondition check
					if (allActions[i]->CheckPreCons(&current->stateAtNode))
					{
						MPlannerNode tempNode;

						tempNode.stateAtNode = *allActions[i]->ApplyPostCons(&current->stateAtNode);
						tempNode.action_edge = (MActionTypes)i;
						tempNode.cameFrom = current;

						tempNode.g = allActions[i]->actCost + current->g;
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
								if (current->f + CalculateHeuristic(current->stateAtNode, tempNode.stateAtNode) < openSet[idx].f)
								{
									openSet[idx].g = current->g + CalculateHeuristic(current->stateAtNode, openSet[idx].stateAtNode);
									openSet[idx].f = openSet[idx].g + openSet[idx].h;
									openSet[idx].cameFrom = current;
								}
							}
						}
					}
				}
			}
		} while (!openSet.empty() && !isRouteFound);
	}

private:
	/** @brief Gets the i
	*
	* @param state The state for which to find 
	* @param goal Goal World state.
	* @return int Index
	*/
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