#include "stdafx.h"
#include "HitboxComponent.h"


HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	:sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	//Positioning and sizing of hitbox to sprite size
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	/*this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Red);*/

	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;
	
	this->OffsetGridX = 50 - width; // These represent the difference between the width and height of the hitbox and the gridsize
	this->offsetGridY = 50 - height; //TODO: if i want this to be versitile I need to include a parameter for the games grid size

}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

const sf::FloatRect HitboxComponent::getHitboxGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}

const sf::Vector2f& HitboxComponent::getPosition()
{
	return this->hitbox.getPosition();
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
	this->hitbox.setPosition(position);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}