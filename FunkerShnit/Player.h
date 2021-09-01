#ifndef PLAYER_H
#define PLAYER_H



#include "Entity.h"



class Player : public Entity
{

private:
	/**** DATA MEMBERS ****/
	sf::SoundBuffer buffer;
	sf::Sound footSteps;

	/* Sword */
	sf::Texture swordTexture;
	Sword* sword;

	/* View */
	sf::RenderWindow* currWindow;

	/* Skills */
	

	/**** METHODS(Private) ****/
	void initSounds();
	void initSword();
	void initGui();

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Player(float x, float y, sf::Texture& texture, int health = 10);
	virtual ~Player();


	/**** ACCESSORS ****/
	const int& getMovementState() const;
	const sf::FloatRect getSwordPosition() const;
	SkillComponent* getSkills(int skill_to_get);
	

	void toggleSwordEquip();
	void toggleAttacking();
	void attackStab();
	const bool getAttacking() const;
	

	/**** METHODS ****/
	

	/*** Updates ***/
	void Update(const float& dt, sf::Vector2i mouse_pos_window, int sword_attack_style = 0) override;
	void updateAnimation(const float& dt);
	void updateSounds();
	void updateSword(const float& dt, sf::Vector2i mouse_pos_window, int sword_attack_style);

	/*** Renders ***/
	void Render(sf::RenderTarget& target);


};





#endif