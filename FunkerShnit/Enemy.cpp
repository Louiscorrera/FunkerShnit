#include "stdafx.h"
#include "Enemy.h"
#include "EnemySpawner.h"

Enemy::Enemy(EnemySpawner* spawner)
	:spawner(spawner)
{
	this->enemyMoveCycle = 0.f; //start cycle at 0
	this->enemyVelocity = sf::Vector2f(2.f, 2.f);
	this->followEnabled = false;
	this->enemyAI = new AIComponent();
}

Enemy::~Enemy()
{

}



void Enemy::follow(const float& dt, Player* player_to_follow)
{
	float dx = player_to_follow->getEntityGlobalBounds().left - this->getEntityGlobalBounds().left;
	float dy = player_to_follow->getEntityGlobalBounds().top - this->getEntityGlobalBounds().top;

	float mag = std::sqrt(pow(dx, 2) + pow(dy, 2));
	sf::Vector2f normal((dx / mag) * 50, (dy / mag) * 50);
	this->updateVelocity(normal.x, normal.y, dt);
	this->movementComponent->Update(dt);
}

void Enemy::Update(const float& dt, Player* player_to_follow)
{
	
}

void Enemy::updateEnemyPos(const float& dt, Player* player_to_follow)
{
	this->enemyAI->follow(player_to_follow, this);

	if (this->followEnabled)
	{
		this->follow(dt, player_to_follow);
	}
	else
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
			else if (negativeY == 1)
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
	this->spawner->enemyAmount--;
}

void Enemy::despawn(Entity* player)
{
}


void Enemy::Render(sf::RenderTarget& target)
{
	target.draw(this->entity);
}
