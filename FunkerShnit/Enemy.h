#ifndef ENEMY_H
#define ENEMY_H

class EnemySpawner;
#include "Player.h"





class Enemy: public Entity
{
private:
	/**** DATA MEMBERS ****/
	EnemySpawner* spawner;

	int enemyMoveCycle;
	sf::Vector2f enemyVelocity;


	/**** METHODS(Private) ****/

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Enemy(EnemySpawner* spawner);
	virtual ~Enemy();

	/**** ACCESSORS ****/

	/**** METHODS ****/

	/*** Updates ***/
	virtual void Update(const float& dt) override; //doesnt do anything
	virtual void updateEnemyPos(const float& dt);
	void checkDistanceFromSpawner();
	
	
	void despawn(); //Despawn the spawner
	void despawn(Entity* player); //Just depsawn the enemy, update the spawner

	/*** Renders ***/
	virtual void Render(sf::RenderTarget& target) override; //doesnt do anything

};

#endif // !ENEMY_H