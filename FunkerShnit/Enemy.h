#ifndef ENEMY_H
#define ENEMY_H

class EnemySpawner;
#include "CombatSystem.h"


class AIComponent;


class Enemy: public Entity
{
private:
	/**** DATA MEMBERS ****/
	EnemySpawner* spawner;
	AIComponent* enemyAI;

	
	int enemyMoveCycle;
	sf::Vector2f enemyVelocity;


	/**** METHODS(Private) ****/

protected:

public:

	bool followEnabled;

	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Enemy(EnemySpawner* spawner);
	virtual ~Enemy();

	/**** ACCESSORS ****/


	/**** METHODS ****/
	void follow(const float& dt, Player* player_to_follow);

	/*** Updates ***/
	virtual void Update(const float& dt, Player* player_to_follow); //doesnt do anything
	virtual void updateEnemyPos(const float& dt, Player* player_to_follow);
	void checkDistanceFromSpawner();
	void checkSpawnerDistanceFromPlayer(Player* player);
	
	
	
	void despawn(); //Despawn the spawner
	void despawn(Entity* player); //Just depsawn the enemy, update the spawner

	/*** Renders ***/
	virtual void Render(sf::RenderTarget& target); //doesnt do anything

};


class AIComponent
{
private:
	
protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	AIComponent(){}
	virtual ~AIComponent(){}

	/**** ACCESSORS ****/

	/**** METHODS ****/
	void follow(Entity* player_to_follow, Enemy* Enemy){
		
		float dx = player_to_follow->getEntityGlobalBounds().left - Enemy->getEntityGlobalBounds().left;
		float dy = player_to_follow->getEntityGlobalBounds().top - Enemy->getEntityGlobalBounds().top;

		float mag = std::sqrt(pow(dx, 2) + pow(dy, 2));

		if (mag < 200)
		{
			Enemy->followEnabled = true;
		}
		else
		{
			Enemy->followEnabled = false;
		}
	}

	/*** Updates ***/

	/*** Renders ***/
};
#endif // !ENEMY_H