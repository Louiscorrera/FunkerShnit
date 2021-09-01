#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"

#include "SkillComponent.h"
#include "Sword.h"

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

	/* Trackers */
	int health;
	bool isAlive;
	bool hasAttacked;

	

	/* Movement */
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
	std::vector<SkillComponent*> skillComponents;

	
public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Entity();
	virtual ~Entity();

	/**** ACCESSORS ****/
	const sf::Vector2f& getPosition() const;
	const sf::Sprite& getEntitySprite();
	virtual const sf::FloatRect getEntityGlobalBounds();
	const sf::FloatRect getEntityNextBounds(const float& dt);
	const bool& getIsAlive() const;
	bool getHasAttacked();
	sf::Vector2f getEntityVelocity();
	

	const int& getHitboxOffsetY() const;
	const int& getHitboxOffsetX() const;

	/**** METHODS ****/
	void setTexture(sf::Texture& texture);
	virtual void setPosition(const float x, const float y);


	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet);
	void createHitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createSkillComponent(int number_of_skills = 0);
	
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();


	/** Combat **/
	void takeDamage(int damage);
	void toggleAttacked();

	/*** Updates ***/
	/** Pure Virtuals **/
	virtual void Update(const float& dt); //Does nothing
	virtual void Update(const float& dt, sf::Vector2i mouse_pos_window, int sword_attack_style); //Does nothing
	virtual void updateVelocity(const float& dir_x, const float& dir_y, const float& dt);
	

	/*** Renders ***/
	/** Pure Virtuals **/
	virtual void Render(sf::RenderTarget& target);
};

#endif // !ENTITY_H