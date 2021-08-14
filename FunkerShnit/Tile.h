#ifndef TILE_H
#define TILE_H



class Tile
{

private:
	/**** DATA MEMBERS ****/

	/* Tile Shape/Dimensions */
	sf::RectangleShape tileShape;
	sf::RectangleShape collisionBox;
	unsigned gridPosX;
	unsigned gridPosY;
	float tileWidth;
	float tileHeight;

	/* Tile Attribs */
	bool collison;
	unsigned type;

	/* Graphics */
	

	/**** METHODS(Private) ****/

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/

	Tile(unsigned int grid_pos_x, unsigned int grid_pos_y, float tile_width, float tile_height); /* Tile constructor without a texture (Default) */
	Tile(unsigned int grid_cord_x, unsigned int grid_cord_y, float tile_width, float tile_height, const sf::Texture& tile_texture, const sf::IntRect& texture_selector, bool collision = false, unsigned int type = 1); /* Tile constructor with a texture */
	~Tile();

	/**** ACCESSORS ****/
	const std::string getTileAsString() const;
	const sf::FloatRect& getTileGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const bool& getCollision() const;

	/**** METHODS ****/

	/*** Updates ***/
	void Update(sf::Texture& tile_texture);

	/*** Renders ***/
	void Render(sf::RenderTarget& target);
};

#endif