#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity
{
	private:
	/**** DATA MEMBERS ****/

	/**** METHODS(Private) ****/
	virtual void initVars();

protected:

	/**** DATA MEMBERS ****/
	/* Graphic */
	sf::Sprite entity;

	/* Movement */
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

	
public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Entity();
	virtual ~Entity();

	/**** ACCESSORS ****/
	const sf::Vector2f& getPosition() const;
	const sf::Sprite& getEntitySprite();
	const sf::FloatRect getEntityGlobalBounds();
	const sf::FloatRect getEntityNextBounds(const float& dt);

	const int& getHitboxOffsetY() const;
	const int& getHitboxOffsetX() const;

	/**** METHODS ****/
	void setTexture(sf::Texture& texture);
	virtual void setPosition(const float x, const float y);


	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet);
	void createHitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	/*** Updates ***/
	/** Pure Virtuals **/
	virtual void Update(const float& dt, int sword_attack_style) = 0;
	virtual void updateVelocity(const float& dir_x, const float& dir_y, const float& dt);

	/*** Renders ***/
	/** Pure Virtuals **/
	virtual void Render(sf::RenderTarget& target);
};

#endif // !ENTITY_H