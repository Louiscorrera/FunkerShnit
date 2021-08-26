#include "stdafx.h"
#include "VampireEnemy.h"

void VampireEnemy::initComponents()
{
	this->createHitBoxComponent(this->entity, 50, 50.f, 60, 60.f); //Update these to be more accurate
	this->createMovementComponent(20, 300, 200);
	this->createAnimationComponent(*this->texture);

	/* animations */
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 8, 1, 64, 64); //Update these to be more accurate
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 3, 8, 3, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 10.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 2, 8, 2, 64, 64);
}

VampireEnemy::VampireEnemy(EnemySpawner* spawner, sf::Texture& vampire_sprite_sheet)
	:Enemy(spawner), texture(&vampire_sprite_sheet)
{
	this->isAlive = true;
	this->initComponents();
}

VampireEnemy::~VampireEnemy()
{
}


void VampireEnemy::Update(const float& dt)
{
	this->updateAnimation(dt);
	this->updateEnemyPos(dt);
	this->checkDistanceFromSpawner();
}

void VampireEnemy::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(MOVING_LEFT)) //Left
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity(), false);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) //Right
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity());

	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity());
	}
}
