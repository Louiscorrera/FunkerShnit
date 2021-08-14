#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocit, float acceleration, float deceleration)
	:entity(sprite), maxVelocity(maxVelocit), acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;

		break;
	case MOVING:

		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;

		break;
	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;

		break;
	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;
	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;
	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;

		break;
	default:
		break;
	}
	return false;
}

void MovementComponent::Update(const float& dt)
{
	/** Check Right <-> Left Movement **/

	/* Check Right */
	if (this->velocity.x > 0.f)
	{
		/* If Velocity->Right is more than  max velocity
		* --Set Velocity->Right to max velocity */
		if (this->velocity.x > this->maxVelocity) { this->velocity.x = this->maxVelocity; }

		/* Apply friction to Velocity->Right */
		this->velocity.x -= this->deceleration * dt;

		/* Check if stopped, ensure stoped */
		if (this->velocity.x < 0.f) { this->velocity.x = 0.f; }
	}
	/* Check Left */
	else if (this->velocity.x < 0.f)
	{
		/* If Velocity->Left is more than max velocity
		* --Set Velocity->Left to max velocity */
		if (this->velocity.x < -this->maxVelocity) { this->velocity.x = -this->maxVelocity; }

		/* Apply friction to Velocity->Left */
		this->velocity.x += this->deceleration * dt;

		/* Check if stopped, ensure stoped */
		if (this->velocity.x > 0.f) { this->velocity.x = 0.f; }

	}
	else {}

	/* Check Up & Down Movement */

		/* Check Up */
	if (this->velocity.y < 0.f)
	{
		/* If Velocity->Right is more than  max velocity
		* --Set Velocity->Right to max velocity */
		if (this->velocity.y <= -this->maxVelocity) { this->velocity.y = -this->maxVelocity; }

		/* Apply friction to Velocity->Right */
		this->velocity.y += this->deceleration * dt;

		/* Check if stopped, ensure stoped */
		if (this->velocity.y > 0.f) { this->velocity.y = 0.f; }
	}
	/* Check Left */
	else if (this->velocity.y > 0.f)
	{
		/* If Velocity->Right is more than  max velocity
		* --Set Velocity->Right to max velocity */
		if (this->velocity.y > this->maxVelocity) { this->velocity.y = this->maxVelocity; }

		/* Apply friction to Velocity->Right */
		this->velocity.y -= this->deceleration * dt;

		/* Check if stopped, ensure stoped */
		if (this->velocity.y < 0.f) { this->velocity.y = 0.f; }
	}
	else {}


	/** Final Move **/
	this->entity.move(this->velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	this->velocity.x += (this->acceleration * dir_x) * dt;
	this->velocity.y += (this->acceleration * dir_y) * dt;
}
