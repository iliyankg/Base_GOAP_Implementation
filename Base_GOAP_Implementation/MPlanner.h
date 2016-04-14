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
#include "MActionBashDoor.h"
#include "MActionDamageEnemy.h"
#include "MActionFixKeypad.h"
#include "MActionGetKeypadCombo.h"
#include "MActionGetToolsForKeypad.h"

struct MPlannerNode
{
	//Operator overloads
	friend bool operator== (const MPlannerNode& left, const MPlannerNode& right)
	{
		if (left.stateAtNode._facts.size() != right.stateAtNode._facts.size())
			return false;
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
		LOG("Created Planner");
		allActions.push_back(new MActionOpenDoor(1.0f));
		allActions.push_back(new MActionGetKey(1.0f));
		allActions.push_back(new MActionBashDoor(10.0f));
		allActions.push_back(new MActionDamageEnemy(1.0f));
		allActions.push_back(new MActionFixKeypad(1.0f));
		allActions.push_back(new MActionGetKeypadCombo(1.0f));
		allActions.push_back(new MActionGetToolsForKeypad(1.0f));
	}
	~MPLanner() {}
	
	//All possible actions
	std::vector<MAction*> allActions;

	/** @brief Prints the final plan
	*
	* @return Void
	*/
	void PrintPlan(MWMemory& goal, MWMemory& start, std::vector<MActionTypes>* toReturn)
	{
		MPlannerNode tempGoal;

		for (int i = 0; i < closedSet.size(); ++i)
		{
			if (goal == closedSet[i].stateAtNode)
			{
				tempGoal = closedSet[i];
				i = closedSet.size();
			}
				
		}
			

		LOG(tempGoal.action_edge);
		toReturn->push_back(tempGoal.action_edge);
		while (tempGoal.stateAtNode != start)
		{
			tempGoal = *tempGoal.cameFrom;
			LOG(tempGoal.action_edge);
			toReturn->push_back(tempGoal.action_edge);
		}

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
	std::vector<MActionTypes> Plan(MAgent agent)
	{
		std::vector<MActionTypes> toReturn;
		openSet.clear();
		closedSet.clear();

		LOG("Starting Planning");

		MWMemory start = agent.agentMemory;
		MWMemory goal = agent.goalManager.GetNewGoal(start, agent.numAvailableGoals, agent.agentGoals, agent.goalMemory);

		bool isRouteFound = false;
		
		closedSet.clear();
		
		MPlannerNode tempStart;
		tempStart.stateAtNode = start;
		tempStart.action_edge = badaction;
		tempStart.g = 0.0f;
  		tempStart.h = CalculateHeuristic(start, goal);
		tempStart.f = tempStart.h + tempStart.g;
		openSet.push_back(tempStart);	

		do
		{
			LOG(std::endl)
			MPlannerNode* current = new MPlannerNode(openSet[0]);
			openSet.erase(openSet.begin());
			closedSet.push_back(*current);

			if (MWMemory::IsGoalReached(current->stateAtNode, goal))
			{
				LOG("Plan Found");
				isRouteFound = true;
				PrintPlan(goal, start, &toReturn);
				std::reverse(toReturn.begin(), toReturn.end());
				return toReturn;
			}

			bool checkBothActions = false;
			bool applyBothActions = false;

			FACT_TYPES singularTypeToCheck = invalid;
			if (CheckDoubleKeyAction(singularTypeToCheck, current->stateAtNode))
			{
				checkBothActions = true;
				applyBothActions = true;
			}
			

			if (!isRouteFound)
			{
				for (int i = 0; i < agent.numAvailableActions; ++i)
				{
					int actIndex = agent.agentActions[i];
					
					//Precondition check
					bool preconCehck = false;
					if (dynamic_cast<MActionGetKey*>(allActions[actIndex]) && checkBothActions)
					{
						preconCehck = allActions[actIndex]->CheckPreCons(&current->stateAtNode, fct_keyfortoolbox);
						singularTypeToCheck = fct_hasdoorkey;
						i--;
						checkBothActions = false;
					}
					else if (dynamic_cast<MActionGetKey*>(allActions[actIndex]))
						preconCehck = allActions[actIndex]->CheckPreCons(&current->stateAtNode, singularTypeToCheck);
					else
						preconCehck = allActions[actIndex]->CheckPreCons(&current->stateAtNode);

						

					if (preconCehck)
					{
						MPlannerNode tempNode;
						if (dynamic_cast<MActionGetKey*>(allActions[actIndex]) && applyBothActions)
						{
							tempNode.stateAtNode = allActions[actIndex]->ApplyPostCons(current->stateAtNode, fct_keyfortoolbox);
							applyBothActions = false;
						}
						else if (dynamic_cast<MActionGetKey*>(allActions[actIndex]))
							tempNode.stateAtNode = allActions[actIndex]->ApplyPostCons(current->stateAtNode, singularTypeToCheck);
						else
							tempNode.stateAtNode = allActions[actIndex]->ApplyPostCons(current->stateAtNode);

						tempNode.action_edge = (MActionTypes)actIndex;
						tempNode.cameFrom = current;

						tempNode.g = allActions[actIndex]->actCost + current->g;
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
									openSet[idx].action_edge = (MActionTypes)i;
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

	bool CheckDoubleKeyAction(FACT_TYPES& singularType, MWMemory goal)
	{
		std::vector<int> keys = goal.GetAllFactsOfType(fct_key);

		if (keys[0] == -1)
			return false;
		else if (keys.size() == 2)
			return true;
		else
		{
			singularType = goal._facts[goal.GetConfidentFactIdx(fct_key)].GetKeyType();
			return false;
		}
		
		/*int idxOne = goal.GetConfidentFactIdx(fct_hasdoorkey);
		int idxTwo = goal.GetConfidentFactIdx(fct_keyfortoolbox);

		FACT_TYPES singularTypeToCheck = invalid;

		if (idxOne != -1 && idxTwo != -1)
		{
			if (goal._facts[idxOne].GetHasDoorKey() && goal._facts[idxTwo].GetHasKeyForToolbox())
			{
				return true;
			}
			else if (goal._facts[idxOne].GetHasDoorKey())
			{
				singularType = fct_hasdoorkey;
				return false;
			}
			else if (goal._facts[idxTwo].GetHasKeyForToolbox())
			{
				singularType = fct_keyfortoolbox;
				return false;
			}
		}
		else if (idxOne != -1 && goal._facts[idxOne].GetHasDoorKey())
		{
			singularType = fct_hasdoorkey;
			return false;
		}
		else if (idxTwo != -1 && goal._facts[idxTwo].GetHasKeyForToolbox())
		{
			singularType = fct_keyfortoolbox;
			return false;
		}
		else
			return false;*/
	}

	/** @brief Calculates the heuristic between two world states.
	*
	* Currently the heuristic is the number of different facts 
	* between the current state and the goal state.
	*
	* @param MWMemory stateFrom Starting state.
	* @param MWMemory stateTo State to go to.
	* @return float heuristic
	*/
	float CalculateHeuristic(MWMemory& stateFrom, MWMemory& stateTo)
	{
		float counter = 0;

		for (int i = 0; i < stateTo._facts.size(); ++i)
		{
			int idx = stateFrom.GetConfidentFactIdx(stateTo._facts[i].GetFactType());

			if (idx == -1)
			{
				counter++;
			}
			else
			{
				if (stateFrom._facts[idx] != stateTo._facts[i])
					counter++;
			}
			
		}
		return counter;
	}

	/** @brief Inserts a MPLannerNode in a given container.
	*
	* It acts like a priority queue where the value used to sort 
	* the Nodes is the 'F' cost of each node
	*
	* @param vector<MPlannerNode> vec Container to insert into.
	* @param MPlannerNode toInsert State to go to.
	* @return void
	*/
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