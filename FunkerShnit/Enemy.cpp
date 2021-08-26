#include "stdafx.h"
#include "Enemy.h"
#include "EnemySpawner.h"

Enemy::Enemy(EnemySpawner* spawner)
	:spawner(spawner)
{
	this->enemyMoveCycle = 0.f; //start cycle at 0
	this->enemyVelocity = sf::Vector2f(2.f, 2.f);
}

Enemy::~Enemy()
{

}

void Enemy::Update(const float& dt)
{
	
}

void Enemy::updateEnemyPos(const float& dt)
{
	/* if there have been 15 game loop cycles, change enemy velocity and reset counter */
	if (this->enemyMoveCycle >= 350)
	{
		int negativeY = rand() % 3;
		int negativeX = rand() % 2;
		if (negativeY == 0) 
		{
			this->enemyVelocity.y = -(rand() % 10 + 1);
		}
		else if(negativeY == 1)
		{
			this->enemyVelocity.y = rand() % 10 + 1;
		}
		else
		{
			this->enemyVelocity.y = 0.f;
		}
		if (negativeX == 0)
		{
			this->enemyVelocity.x = -(rand() % 10 + 1);
		}
		else if (negativeX == 1)
		{
			this->enemyVelocity.x = rand() % 10 + 1;
		}
		else
		{
			this->enemyVelocity.x = 0.f;
		}
		
		this->enemyMoveCycle = 0;
	}
	else /* if within x amount of game loop cycles move the enemy by its current velocity */
	{
		this->updateVelocity(this->enemyVelocity.x, this->enemyVelocity.y, dt);
		this->movementComponent->Update(dt);
		this->enemyMoveCycle++;
	}
}

void Enemy::checkDistanceFromSpawner()
{
	//Reset enemy if it has traveled too far from the spawner
	if (this->entity.getPosition().x > this->spawner->getSpawnerLocation().x + this->spawner->getSpawnerMaxDistance() 
		|| this->entity.getPosition().x < this->spawner->getSpawnerLocation().x - this->spawner->getSpawnerMaxDistance())
	{
		this->entity.setPosition(this->spawner->getSpawnerLocation());
	}
	if (this->entity.getPosition().y > this->spawner->getSpawnerLocation().y + this->spawner->getSpawnerMaxDistance() 
		|| this->entity.getPosition().y < this->spawner->getSpawnerLocation().y - this->spawner->getSpawnerMaxDistance())
	{
		this->entity.setPosition(this->spawner->getSpawnerLocation());
	}
}

void Enemy::despawn()
{
	
}

void Enemy::despawn(Entity* player)
{
}


void Enemy::Render(sf::RenderTarget& target)
{
	target.draw(this->entity);
}
