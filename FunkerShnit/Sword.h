#pragma once

#include "Weapon.h"
#include "Entity.h"

enum SwordAttack{ DEFAULT = 0, STAB, CRUSH, SLASH, GYRATE };

class Sword :
    public Weapon
{

private:
	/**** DATA MEMBERS ****/

	/* Sword Texture Rect */
	sf::FloatRect textureRect;

	/* Sword Hitbox */
	HitboxComponent* swordHitboxComponent;

	/* Sword State */
	int swordAttack;
	bool isAttacking;
	sf::Vector2f swingVelocity;

	
	/* Sword Range */
	sf::FloatRect entityBounds;
	sf::FloatRect swordBounds;

	/* Sword Controls */
	bool isEquipped;
	float attackTimer;
	float attackTimerReset;

	/**** METHODS(Private) ****/
	void initTexture();
	void initVars();

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Sword(std::string item_name, unsigned int item_level, unsigned int item_value, unsigned int item_weight, 
		bool item_wieldable, bool item_consumable, 
		sf::Texture& item_texture);
	virtual ~Sword();

	/**** ACCESSORS ****/
	const bool& getSwordEquipped() const; 
	const bool& getSwordState() const;
	const bool& getAttackTimer();

	void toggleEquip();
	void toggleAttacking();

	/**** METHODS ****/

	/*** Updates ***/
	void Update(const float& dt);
	void updateSwordAttack(int sword_attack = SwordAttack::DEFAULT);
	void updateAttackTimer(const float& dt);
	void updateSwordRanges(sf::FloatRect playerBounds);

	void animateSword(sf::FloatRect playerBounds);
	void resetSword();

	/*** Renders ***/
	void Render(sf::RenderTarget& target);

};

