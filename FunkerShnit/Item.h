#ifndef ITEM_H
#define ITEM_H



class Item
{
private:
	/**** DATA MEMBERS ****/


	/**** METHODS(Private) ****/
	virtual void initTexture();

protected:

	/* Item Name */
	std::string name;

	/* Stats */
	unsigned int level;
	unsigned int value;
	unsigned int weight;

	/* Types */
	bool wieldable;
	bool consumable;

	/* Graphic */
	sf::Sprite item;
	sf::Texture* itemTexture;

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Item(std::string item_name, unsigned int item_level, unsigned int item_value, unsigned int item_weight, bool item_wieldable, bool item_consumable, sf::Texture& item_texture);
	virtual ~Item();

	/**** ACCESSORS ****/

	/**** METHODS ****/
	

	/*** Updates ***/
	virtual void Update(const float& dt) = 0;

	/*** Renders ***/
	virtual void Render(sf::RenderTarget& target) = 0;

};



#endif // !ITEM_H