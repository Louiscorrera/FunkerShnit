#include "stdafx.h"
#include "Weapon.h"

void Weapon::initTexture()
{
}

Weapon::Weapon(std::string item_name, unsigned int item_level, unsigned int item_value, unsigned int item_weight, bool item_wieldable, bool item_consumable, sf::Texture& item_texture)
	:Item(item_name, item_level, item_value, item_weight, item_wieldable, item_consumable, item_texture)
{
	this->initTexture();
}

Weapon::~Weapon()
{
}


void Weapon::Update(const float& dt)
{
}

void Weapon::Render(sf::RenderTarget& target)
{
}
