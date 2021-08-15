#ifndef PLAYER_H
#define PLAYER_H


#include "Sword.h"



class Player : public Entity
{

private:
	/**** DATA MEMBERS ****/
	sf::SoundBuffer buffer;
	sf::Sound footSteps;

	/* Sword */
	sf::Texture swordTexture;
	Sword* sword;

	/**** METHODS(Private) ****/
	void initSounds();
	void initSword();

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();


	/**** ACCESSORS ****/
	const int& getMovementState() const;

	void toggleSwordEquip();
	void toggleAttacking();

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