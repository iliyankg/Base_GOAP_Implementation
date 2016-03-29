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
	fct_dooropen,
	fct_hasdoorkey,
	fct_keypadfixed,
	fct_toolsforkeypad,
	fct_toolboxopen,
	fct_lockpickfortoolbox,
	fct_keyfortoolbox,
	fct_keypadcombonote,
	fct_enemyhealth
};

struct MWMFact
{
	//Operator overloads
	friend inline bool operator== (const MWMFact& left, const MWMFact& right)
	{		
		if (left._doorOpen != right._doorOpen)
			return false;
		if (left._hasDoorKey != right._hasDoorKey)
			return false;
		if (left._iskeypadFixed != right._iskeypadFixed)
			return false;
		if(left._hasToolsForKeypad != right._hasToolsForKeypad)
			return false;
		if(left._isToolBoxOpened != right._isToolBoxOpened)
			return false;
		if(left._hasLockpick != right._hasLockpick)
			return false;
		if(left._hasKeyForToolbox != right._hasLockpick)
			return false;
		if(left._keypadCombination != right._keypadCombination)
			return false;
		if (left._enemyHealth != right._enemyHealth)
			return false;

		return true;
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
	FACT_TYPES	GetFactType()			{ return _fact_type; }
	float		GetConfidance()			{ return _confidance; }
	bool		GetDoorOpen()			{ return _doorOpen; }	
	bool		GetHasDoorKey()			{ return _hasDoorKey; }
	bool		GetIsKeypadFixed()		{ return _iskeypadFixed; }
	bool		GetHasToolsForKeypad()	{ return _hasToolsForKeypad; }
	bool		GetIsToolBoxOpen()		{ return _isToolBoxOpened; }
	bool		GetHasLockpick()		{ return _hasLockpick; }
	bool		GetHasKeyForToolbox()	{ return _hasKeyForToolbox; }
	int			GetKeypadCombo()		{ return _keypadCombination; }
	float		GetEnemyHealth()		{ return _enemyHealth; }

	//Setters
	void		SetDoorOpen(bool val)			{ _doorOpen = val; }
	void		SetHasDoorKey(bool val)			{ _hasDoorKey = val; }
	void		SetIsKeypadFixed(bool val)		{ _iskeypadFixed = val; }
	void		SetHasToolsForKeypad(bool val)	{ _hasToolsForKeypad = val; }
	void		SetIsToolBoxOpened(bool val)	{ _isToolBoxOpened = val; }
	void		SetHasLockpick(bool val)		{ _hasLockpick = val; }
	void		SetHasKeyForToolbox(bool val)	{ _hasKeyForToolbox = val; }
	void		SetKeypadCombo(int val)			{ _keypadCombination = val; }
	void		SetEnemyHealth(float val)		{ _enemyHealth = val; }


private:
	FACT_TYPES _fact_type;	//Fact type
	float _confidance;		//Fact confidance value

	bool _doorOpen;			//Door open or not
	bool _hasDoorKey;		//Has key or not
	bool _iskeypadFixed;	//Door keypad fixed
	bool _hasToolsForKeypad;//Can fix keypad
	bool _isToolBoxOpened;	//Toolbox is open
	bool _hasLockpick;		//Can atempt to open toolbox with lockpick
	bool _hasKeyForToolbox;	//Can open toolbox
	int	 _keypadCombination; //Combination for keypad
	float _enemyHealth;		//Health Value
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


	/** @brief Specific comparator method for a reached goal
	*
	* @param current State to check.
	* @param goal Goal to check against.
	* @return Returns true if goal is satisfied.
	*/
	static inline bool IsGoalReached(MWMemory& current, MWMemory& goal)
	{
		float counter = 0;

		for (int i = 0; i < goal._facts.size(); ++i)
		{
			int idx = current.GetConfidentFactIdx(current._facts[i].GetFactType());

			if (idx == -1)
			{
				return false ;
			}
			else
			{
				if (current._facts[idx] != goal._facts[i])
					return false;
			}
		}
		return true;
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
	template <class T>
	void CreateFact(FACT_TYPES type, T val)
	{
		MWMFact tempFact = MWMFact(type);
		
		switch (type)
		{
		case fct_dooropen:
			tempFact.SetDoorOpen(val);
			break;
		case fct_hasdoorkey:
			tempFact.SetHasDoorKey(val);
			break;
		case fct_keypadfixed:
			tempFact.SetIsKeypadFixed(val);
			break;
		case fct_toolsforkeypad:
			tempFact.SetHasToolsForKeypad(val);
			break;
		case fct_toolboxopen:
			tempFact.SetIsToolBoxOpened(val);
			break;
		case fct_lockpickfortoolbox:
			tempFact.SetHasLockpick(val);
			break;
		case fct_keyfortoolbox:
			tempFact.SetHasKeyForToolbox(val);
			break;
		case fct_keypadcombonote:
			tempFact.SetKeypadCombo(val);
			break;
		case fct_enemyhealth:
			tempFact.SetEnemyHealth(val);
		default:
			break;
		}

		_facts.push_back(tempFact);
		_facts.back().ID = _facts.size() - 1;
	}
	
	//All facts in memory.
	std::vector<MWMFact> _facts;
};