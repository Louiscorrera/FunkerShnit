#include "stdafx.h"
#include "Item.h"

void Item::initTexture()
{
}

Item::Item(std::string item_name, unsigned int item_level, unsigned int item_value, unsigned int item_weight, bool item_wieldable, bool item_consumable, sf::Texture& item_texture)
	:name(item_name), level(item_level), value(item_value), weight(item_weight), wieldable(item_wieldable), consumable(item_consumable), itemTexture(&item_texture)
{
	this->item.setTexture(item_texture);

}

Item::~Item()
{


}
