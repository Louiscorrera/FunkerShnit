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
		if (player.getSwordPosition().intersects(Enemy.getEntityGlobalBounds()) && player.getAttacking()) 
		{
			/* Get players attack level */
			int playerAttack = player.getSkills(Skills::ATTACK)->getSkillLevel();
			int damage = playerAttack;
			/* Cause dmg dependent on attack level to enemy */
			/* Reduce enemies health */
			Enemy.takeDamage(damage);
			/* Check if enemy is dead */
			/* If dead give player exp relative to the enemy level && loot */
			if (!Enemy.getIsAlive())
			{
				player.getSkills(Skills::ATTACK)->gainExperience(20);
			}
			/* Despawn enemy */
		}
	}
}
