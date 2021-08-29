#include "stdafx.h"
#include "EnemySpawner.h"



void EnemySpawner::initVars()
{
	this->maxEnemyDistance = 400.f;

	this->spawnerDone = false;
	this->spawnerActive = false;

	this->spawnTimer = 0.f;
	this->spawnTimerMax = 300.f;
}

EnemySpawner::EnemySpawner(sf::Texture& enemy_texture, sf::Vector2f tile_pos, int enemy_type, int enemy_level, int enemy_amount, int max_enemy_amount)
	:texture(&enemy_texture), spawnerPosition(tile_pos), enemyType(enemy_type), enemyLevel(enemy_level), enemyAmount(enemy_amount), maxEnemyAmount(max_enemy_amount)
{
	this->initVars();
}

EnemySpawner::~EnemySpawner()
{
}

const bool EnemySpawner::getEnemySpawnTimer()
{
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->spawnTimer = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

const bool& EnemySpawner::getSpawnerDone()
{
	return this->spawnerDone;
}

const bool& EnemySpawner::getSpawnerActive()
{
	return this->spawnerActive;
}

bool EnemySpawner::getIsFull()
{
	if (this->enemyAmount >= this->maxEnemyAmount)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const sf::Vector2f& EnemySpawner::getSpawnerLocation()
{
	return this->spawnerPosition;
}

const float& EnemySpawner::getSpawnerMaxDistance()
{
	return this->maxEnemyDistance;
}

void EnemySpawner::toggleSpawnerActive()
{
	this->spawnerActive = !this->spawnerActive;
}





void EnemySpawner::Update(const float& dt)
{
	this->updateTimer(dt);
}

void EnemySpawner::updateTimer(const float& dt)
{
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 100.f * dt;
	}else {}
}




/* This is a call for a resource from tilemap, meant to be called from gamestate */
Enemy* EnemySpawner::spawnEnemy()
{
	
	if (this->enemyAmount >= this->maxEnemyAmount) //If the max amount of enemies have been spawned switch spawner done to true
	{
		this->spawnerDone = true;
	}
	
	if (this->spawnerDone) //Check if spawner has max amount of enemies
	{
		return NULL;
	}
	else //Spawn 
	{
		
		return this->chooseEnemyType();
	}

}

Enemy* EnemySpawner::chooseEnemyType()
{
	if (this->enemyType == 0) //First enemy type
	{
		this->enemyAmount++;
		return new VampireEnemy(this, *this->texture);
	}
	else if (this->enemyType == 1) //Second enemy type
	{
		//return new MummyEnemy(this, *this->texture);
	}
}

void EnemySpawner::Render(sf::RenderTarget& target)
{
}
