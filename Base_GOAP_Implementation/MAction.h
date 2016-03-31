/** @file MAction.h
*   @brief Base Action class and MActionTypes enums.
*
*  @author Iliyan Georgiev
*  @bug No known bugs.
*/
#pragma once
#include "MWorkingMemory.h"

//Enumerated list of all actions possible
enum MActionTypes
{
	badaction = -1,
	act_opendoor,
	act_getdoorkey,
	act_bashdoor,
	act_damageenemy,
	num_actions
};

class MAction
{
public:
	MAction() {}
	~MAction() {}

	//Flat cost for action to be performed.
	float actCost;


	/** @brief Pure virtual method used to check if action preconditions are met.
	* 
	* @param state Current state to compare to.
	* @return True or False if the action pre-conditions are met.
	*/
	virtual bool CheckPreCons(MWMemory* state) { LOG("BASE CHECK PRECON RAN"); return false; }
	virtual bool CheckPreCons(MWMemory* state, FACT_TYPES type) { LOG("BASE CHECK PRECON RAN"); return false; }
	
	/** @brief Pure virtual method used to apply post conditions to a world state
	*
	* Used to create the World State nodes during the planning stage. 
	*
	* @param state Current state to modify.
	* @return A pointer ot the NEWed world state with the post conditions applied to it.
	*/
	virtual MWMemory ApplyPostCons(MWMemory state) { LOG("BASE APPLY POST RAN"); return state; }
	virtual MWMemory ApplyPostCons(MWMemory state, FACT_TYPES type) { LOG("BASE APPLY POST RAN"); return state; }
};