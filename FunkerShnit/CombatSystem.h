#pragma once

#include "Player.h"

class CombatSystem
{

private:
	/**** DATA MEMBERS ****/


	/**** METHODS(Private) ****/

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	CombatSystem();
	virtual ~CombatSystem();

	/**** ACCESSORS ****/

	/**** METHODS ****/
	void battle(Player& player, Entity& Enemy, Entity* Enemy2 = NULL);

	/*** Updates ***/

	/*** Renders ***/
};

