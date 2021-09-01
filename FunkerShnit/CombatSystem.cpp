#include "stdafx.h"
#include "CombatSystem.h"

CombatSystem::CombatSystem()
{
}

CombatSystem::~CombatSystem()
{
}

void CombatSystem::battle(Player& player, Entity& Enemy, Entity* Enemy2)
{
	/* Only one enemy */
	if (!Enemy2) {

		/* Check if sword has gone within bounds of enemy */
		if (player.getSwordPosition().intersects(Enemy.getEntityGlobalBounds()) && player.getAttacking() && player.getHasAttacked() == false) 
		{
			/* Get players attack level */
			int playerAttack = player.getSkills(Skills::ATTACK)->getSkillLevel();
			int damage = playerAttack;
			/* Cause dmg dependent on attack level to enemy */
			/* Reduce enemies health */
				
			
			Enemy.takeDamage(damage);
			Enemy.updateGui(damage);
			player.toggleAttacked();
			/* Check if enemy is dead */
			/* If dead give player exp relative to the enemy level && loot */
			if (!Enemy.getIsAlive())
			{
				player.getSkills(Skills::ATTACK)->gainExperience(20);
				std::cout << "EXP\n";
			}else{}
			/* Despawn enemy */
		}
		else {  }
	}
	else {}
}
