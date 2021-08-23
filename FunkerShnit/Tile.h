#ifndef TILE_H
#define TILE_H

#include "EnemySpawner.h"


enum TileType {REGULAR = 0, COLLISION, DEFERRED, DAMAGE, ANIMATED, ENEMY};
enum EnemyType { ENEMY1 = 0, ENEMY2, ENEMY3 };

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

	int enemyType;


	AnimationComponent* animationComponent;

	
	/**** METHODS(Private) ****/
	void initEnemySpawner(int enemyType, sf::Texture* enemy_texture);

protected:


public:

	/* Tile Attribs */
	bool collison;
	unsigned type;

	/* Enemy Spawner */
	EnemySpawner* enemySpawner;


public:

	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Tile(unsigned int grid_pos_x, unsigned int grid_pos_y, float tile_width, float tile_height); /* Tile constructor without a texture (Default) */
	Tile(unsigned int grid_cord_x, unsigned int grid_cord_y, float tile_width, float tile_height, 
		const sf::Texture& tile_texture, const sf::IntRect& texture_selector, 
		bool collision = false, unsigned int type = 0, 
		int enemy_type = -1, sf::Texture* enemyTexture = NULL); /* Tile constructor with a texture */
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