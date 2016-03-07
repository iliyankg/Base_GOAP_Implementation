/** @file MAction.h
*   @brief Contains MWMFact class; MWMemory class; and fact types as enumerated list.
*
*  @author Iliyan Georgiev
*  @bug No known bugs.
*/

#pragma once
#define LOG(toLog) (std::cout << toLog << std::endl);

#include <iostream>
#include <vector>

enum FACT_TYPES
{
	invalid = -1,
	fct_door,
	fct_haskey
};

struct MWMFact
{
	//Operator overloads
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

	//Fact ID
	int ID;

	//Getters
	FACT_TYPES	GetFactType() { return _fact_type; }
	float		GetConfidance() { return _confidance; }
	bool		GetDoorOpen() { return _doorOpen; }	
	bool		GetHasKey() { return _hasKey; }
	
	glm::vec3 GetPosition() { return _position; }

	//Setters
	void		SetDoorOpen(bool val) { _doorOpen = val; }
	void		SetHasKey(bool val) { _hasKey = val; }

private:
	FACT_TYPES _fact_type;	//Fact type
	float _confidance;		//Fact confidance value

	glm::vec3 _position;	//Position
	bool _doorOpen;			//Door open or not
	bool _hasKey;			//Has key or not
};

class MWMemory
{
public:
	//Operator Overloads
	friend inline bool operator== (const MWMemory& left, const MWMemory& right)
	{
		for (int i = 0; i < left._facts.size(); ++i)
		{
			if (left._facts[i] != right._facts[i])
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

	/** @brief Returns an index to the fact with highest cofidance.
	*
	* @param type Type of fact to look for.
	* @return Index to the highest confidance fact.
	*/
	int GetConfidentFactIdx(FACT_TYPES type)
	{
		MWMFact tempFact = _facts[0];

		int index = -1;

		for (int i = 0; i < _facts.size(); ++i)
		{
			if (_facts[i].GetFactType() == type && _facts[i].GetConfidance() >= tempFact.GetConfidance())
			{
				tempFact = _facts[i];
				index = i;
			}
		}
		return index;
	}

	/** @brief Creates a fact with the specified value for a default.
	*
	* @param type Type of fact to look for.
	* @param val Value to default the fact to.
	* @return void
	*/
	void CreateFact(FACT_TYPES type, bool val)
	{
		MWMFact tempFact = MWMFact(type);
		
		switch (type)
		{
		case fct_door:
			tempFact.SetDoorOpen(val);
			break;
		case fct_haskey:
			tempFact.SetHasKey(val);
			break;
		default:
			break;
		}

		_facts.push_back(tempFact);
		_facts.back().ID = _facts.size() - 1;
	}
	
	//All facts in memory.
	std::vector<MWMFact> _facts;
};