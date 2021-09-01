#include "stdafx.h"
#include "VampireEnemy.h"

void VampireEnemy::initComponents()
{
	this->createHitBoxComponent(this->entity, 15.f, 15.f, 32.f, 35.f);
	this->createMovementComponent(45, 300, 200); 
	this->createAnimationComponent(*this->texture);

	this->entityGui = new EntityGui(this, this->health);

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
	this->health = 5;
	this->initComponents();
	
}

VampireEnemy::~VampireEnemy()
{
}

const sf::FloatRect VampireEnemy::getEntityGlobalBounds()
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getHitboxGlobalBounds();
	}

	return this->entity.getGlobalBounds();
}


void VampireEnemy::Update(const float& dt, Player* player_to_follow)
{
	this->hitboxComponent->update();
	this->updateAnimation(dt);
	this->updateEnemyPos(dt, player_to_follow);
	this->checkDistanceFromSpawner();
	this->entityGui->Update(dt);
	
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

void VampireEnemy::Render(sf::RenderTarget& target)
{
	target.draw(this->entity);
	this->hitboxComponent->render(target);
	this->entityGui->Render(target);
}
