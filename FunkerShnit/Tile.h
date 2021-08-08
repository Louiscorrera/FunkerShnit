#ifndef TILE_H
#define TILE_H



class Tile
{

private:
	/**** DATA MEMBERS ****/

	/* Tile Shape/Dimensions */
	sf::RectangleShape tileShape;
	unsigned gridPosX;
	unsigned gridPosY;
	float tileWidth;
	float tileHeight;

	/* Graphics */
	

	/**** METHODS(Private) ****/

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/

	Tile(unsigned int grid_pos_x, unsigned int grid_pos_y, float tile_width, float tile_height); /* Tile constructor without a texture (Default) */
	Tile(unsigned int grid_cord_x, unsigned int grid_cord_y, float tile_width, float tile_height, const sf::Texture& tile_texture, const sf::IntRect& texture_selector); /* Tile constructor with a texture */
	~Tile();

	/**** ACCESSORS ****/
	const std::string getTileAsString() const;

	/**** METHODS ****/

	/*** Updates ***/
	void Update(sf::Texture& tile_texture);

	/*** Renders ***/
	void Render(sf::RenderTarget& target);
};

#endif