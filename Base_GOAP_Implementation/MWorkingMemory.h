#pragma once
#define LOG(toLog) (std::cout << toLog << std::endl);

#include <vector>
#include <unordered_map>

enum FACT_TYPES
{
	invalid = -1,
	fct_door,
	fct_haskey
};

struct MWMFact
{
	friend inline bool operator== (const MWMFact& left, const MWMFact& right)
	{		
		bool toReturn = true;

		if (left._doorOpen != right._doorOpen)
			toReturn = false;
		if (left._hasKey != right._hasKey)
			toReturn = false;

		return toReturn;
	}
	friend inline bool operator!= (const MWMFact& left, const MWMFact& right)
	{
		return !(left == right);
	}
	
	MWMFact() {}
	MWMFact(FACT_TYPES type)
	{
		_fact_type = type;
		_confidance = 1.0f;
	}

	int ID;

	FACT_TYPES	GetFactType() { return _fact_type; }
	float		GetConfidance() { return _confidance; }
	bool		GetDoorOpen() { return _doorOpen; }	
	bool		GetHasKey() { return _hasKey; }

	void		SetDoorOpen(bool val) { _doorOpen = val; }
	void		SetHasKey(bool val) { _hasKey = val; }

	glm::vec3 GetPosition() { return _position; }

private:
	FACT_TYPES _fact_type;
	float _confidance;

	glm::vec3 _position;
	bool _doorOpen;
	bool _hasKey;
};

class MWMemory
{
public:
	friend inline bool operator== (const MWMemory& left, const MWMemory& right)
	{
		for (int i = 0; i < left._facts.size(); ++i)
		{
			if (*left._facts[i] != *right._facts[i])
				return false;
		}
		return true;
	}
	friend inline bool operator!= (const MWMemory& left, const MWMemory& right)
	{
		return !(left == right);
	}

	MWMemory() {}
	~MWMemory() {}

	int GetConfidentFactIdx(FACT_TYPES type)
	{
		MWMFact* tempFact = _facts[0];

		int index = 0;

		for (int i = 0; i < _facts.size(); ++i)
		{
			if (_facts[i]->GetFactType() == type && _facts[i]->GetConfidance() >= tempFact->GetConfidance())
			{
				tempFact = _facts[i];
				index = i;
			}
		}
		return index;
	}

	void CreateFact(FACT_TYPES type, bool val)
	{
		MWMFact* tempFact = new MWMFact(type);
		
		switch (type)
		{
		case fct_door:
			tempFact->SetDoorOpen(val);
			break;
		case fct_haskey:
			tempFact->SetHasKey(val);
			break;
		default:
			break;
		}

		_facts.push_back(tempFact);
		_facts.back()->ID = _facts.size() - 1;
	}
	
	std::vector<MWMFact*> _facts;
};