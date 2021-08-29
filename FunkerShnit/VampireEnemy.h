#ifndef VAMPYREENEMY_H
#define VAMPYREENEMY_H

#include "Enemy.h"


class VampireEnemy: public Enemy
{
private:
	/**** DATA MEMBERS ****/
	sf::Texture* texture;
	

	/**** METHODS(Private) ****/
	void initComponents();

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	VampireEnemy(EnemySpawner* spawner, sf::Texture& vampire_sprite_sheet);
	virtual ~VampireEnemy();

	/**** ACCESSORS ****/
	const sf::FloatRect getEntityGlobalBounds();

	/**** METHODS ****/

	/*** Updates ***/
	void Update(const float& dt) override;

	void updateAnimation(const float& dt);
	

	/*** Renders ***/
	void Render(sf::RenderTarget& target);


};

#endif // !VAMPYREENEMY_H