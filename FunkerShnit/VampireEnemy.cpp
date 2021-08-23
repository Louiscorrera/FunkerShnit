#include "stdafx.h"
#include "VampireEnemy.h"

void VampireEnemy::initComponents()
{
	this->createHitBoxComponent(this->entity, 50, 50.f, 60, 60.f); //Update these to be more accurate
	this->createMovementComponent(100, 1000, 700);
	this->createAnimationComponent(*this->texture);

	/* animations */
	this->animationComponent->addAnimation("Left", 10.f, 0, 0, 12, 0, 100, 100); //Update these to be more accurate
	this->animationComponent->addAnimation("Right", 10.f, 0, 0, 12, 0, 100, 100);
	this->animationComponent->addAnimation("Up", 10.f, 0, 0, 12, 0, 100, 100);
	this->animationComponent->addAnimation("Down", 10.f, 0, 0, 12, 0, 100, 100);
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
