#include "stdafx.h"
#include "Entity.h"

void Entity::initVars()
{
	this->movementComponent = NULL;
}

Entity::Entity()
{
	this->initVars();
}

Entity::~Entity()
{
	delete this->animationComponent;
	delete this->movementComponent;
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
	{
		return sf::Vector2f(this->hitboxComponent->getHitboxGlobalBounds().left, this->hitboxComponent->getHitboxGlobalBounds().top);
	}
	return this->entity.getPosition();
}

const sf::Sprite& Entity::getEntitySprite()
{
	return this->entity;
}

const sf::FloatRect Entity::getEntityGlobalBounds()
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getHitboxGlobalBounds();
	}

		return this->entity.getGlobalBounds();
}

const sf::FloatRect Entity::getEntityNextBounds(const float& dt)
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}
}

const int& Entity::getHitboxOffsetY() const
{
	return this->hitboxComponent->offsetGridY;
}

const int& Entity::getHitboxOffsetX() const
{
	return this->hitboxComponent->OffsetGridX;
}

void Entity::setTexture(sf::Texture& texture)
{
	this->entity.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->entity, maxVelocity, acceleration, deceleration);

}

void Entity::createAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->entity, textureSheet);
}

void Entity::createHitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::stopVelocity()
{
	this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	this->movementComponent->stopVelocityY();
}



void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
	{
		this->hitboxComponent->setPosition(sf::Vector2f(x, y));
	}
	else
		this->entity.setPosition(x, y);
}

void Entity::updateVelocity(const float& dir_x, const float& dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity

	}
}

void Entity::Render(sf::RenderTarget& target)
{
	target.draw(this->entity);
}

