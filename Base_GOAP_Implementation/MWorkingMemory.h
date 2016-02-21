#pragma once
#include <vector>
#include <unordered_map>

#include "MNode.h"

enum FACT_TYPES
{
	invalid = -1,
	node,
	atnode
};

struct MWMFact
{
	MWMFact() {}
	MWMFact(FACT_TYPES type)
	{
		_fact_type = type;
		_confidance = 1.0f;
	}

	FACT_TYPES	GetFactType() { return _fact_type; }
	float		GetConfidance() { return _confidance; }
	
	void SetPosition(glm::vec3& pos) { _position = pos; }
	void SetNodeHandle(MNode* node)
	{
		_handle = node;
		_position = _handle->_position;
	}

	glm::vec3 GetPosition() { return _position; }
	MNode* GetNodeHandle() { return _handle; }

private:
	FACT_TYPES _fact_type;
	float _confidance;

	glm::vec3 _position;
	
	MNode* _handle;
};

class MWMemory
{
public:
	MWMemory() {}
	~MWMemory() {}

	void GetConfidentNodeFact()
	{
		MWMFact* tempFact = _facts[0];

		for (int i = 0; i < _facts.size(); ++i)
		{
			if (_facts[i]->GetFactType() == node && _facts[i]->GetConfidance() > tempFact->GetConfidance())
				tempFact = _facts[i];
		}
	}

	void CreateFact(FACT_TYPES type, MNode* handle)
	{
		MWMFact* tempFact = new MWMFact(type);
		tempFact->SetNodeHandle(handle);

		_facts.push_back(tempFact);
	}
	
private:
	std::vector<MWMFact*> _facts;
};