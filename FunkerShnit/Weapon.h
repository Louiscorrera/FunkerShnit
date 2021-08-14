#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"


class Weapon : public Item
{

private:
	/**** DATA MEMBERS ****/


	/**** METHODS(Private) ****/
	virtual void initTexture();

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Weapon(std::string item_name, unsigned int item_level, unsigned int item_value, unsigned int item_weight, bool item_wieldable, bool item_consumable, sf::Texture& item_texture);
	virtual ~Weapon();

	/**** ACCESSORS ****/

	/**** METHODS ****/

	/*** Updates ***/
	virtual void Update(const float& dt);

	/*** Renders ***/
	virtual void Render(sf::RenderTarget& target) override;


};

#endif // !WEAPON_H