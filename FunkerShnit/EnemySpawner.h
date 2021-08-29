#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

class Enemy;


#include "VampireEnemy.h"


class EnemySpawner
{
private:
	/**** DATA MEMBERS ****/
	int enemyType;
	int enemyLevel;
	int maxEnemyAmount;
	float maxEnemyDistance;

	bool spawnerDone;
	bool spawnerActive;

	float spawnTimer;
	float spawnTimerMax;
	sf::Vector2f spawnerPosition;

	sf::Texture* texture;

	/**** METHODS(Private) ****/
	void initVars();

protected:

public:
	int enemyAmount;

	/**** CONSTRUCTOR | DESTRUCTOR ****/
	EnemySpawner(sf::Texture& enemy_texture, sf::Vector2f tile_pos, int enemy_type, int enemy_level, int enemy_amount, int max_enemy_amount);
	virtual ~EnemySpawner();

	/**** ACCESSORS ****/
	const bool getEnemySpawnTimer();
	const bool& getSpawnerDone();
	const bool& getSpawnerActive();
	bool getIsFull();
	const sf::Vector2f& getSpawnerLocation();
	const float& getSpawnerMaxDistance();

	/*** Mutators ***/
	void toggleSpawnerActive();
	

	/**** METHODS ****/

	/*** Updates ***/
	virtual void Update(const float& dt);
	void updateTimer(const float& dt);


	Enemy* spawnEnemy();
	Enemy* chooseEnemyType();

	
	/*** Renders ***/
	virtual void Render(sf::RenderTarget& target);
};

#endif // !ENEMYSPAWNER_H