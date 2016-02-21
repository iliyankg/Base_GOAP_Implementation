#pragma once
#include <vector>

#include "MWorkingMemory.h"
#include "MNode.h"

class MNodeSensor
{
private:
	std::vector<MNode*> _allNodes;
	float _viewRadius;
public:
	MNodeSensor(float viewRad) { _viewRadius = viewRad; }
	~MNodeSensor() {}
	
	//Adds a new node to the list of _allNodes.
	void RegisterNewNode(MNode* nodeToReg) { _allNodes.push_back(nodeToReg); }

	//Polls the node sensor and gathers all nodes in the vacinity depitcted by _viewRadius.
	std::vector<MNode> PollNodeSensor(glm::vec3& position, MWMemory& toDeposit)
	{
		for (int i = 0; i < _allNodes.size(); ++i)
		{
			if ((position - _allNodes[i]->_position).length() < _viewRadius)
			{
				toDeposit.CreateFact(node, _allNodes[i]);
			}
		}
	}
};