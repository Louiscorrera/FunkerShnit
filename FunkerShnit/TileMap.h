#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Player.h"


class TileMap
{
private:
	/**** DATA MEMBERS ****/

	/* Storage */
	std::vector<std::vector<std::vector<std::vector<Tile*> > > > tileMap;

	/* Tile Textures */
	sf::Texture tileTextureSheet;
	sf::IntRect* textureSelector;

	/* Deferred Render */
	std::stack<Tile*> deferredRenderStack;

	/* Dimensions */
	float maxSizeX;
	float maxSizeY;
	float maxLayers;
	float maxTiles;
	float gridSizeF;

	/* Map Updates */
	bool overWriteEnabled;
	bool collisionEnabled;
	int tileType;

	/* Key Timer */
	float keyTimer;
	float keyTimerMax;

	/**** METHODS(Private) ****/
	void initTextures();

	void clearMap();
	void initTileMap(std::string texture_sheet_file = "");


protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	TileMap(float max_size_x, float max_size_y, float max_layers, float grid_size_f);
	~TileMap();

	/**** ACCESSORS ****/
	void toggleOverwrite();
	void toggleCollision();
	void toggleType();
	const bool& getOverWrite() const;
	const bool& getCollision() const;
	const int& getTileType() const;
	

	/**** METHODS ****/

	void saveTileMap(std::string filename);
	void loadTileMap(std::string filename);

	/*** Updates ***/
	void Update();

	bool addTile(const unsigned int& pos_x, const unsigned int& pos_y, const float& layer, 
		sf::Texture& tile_texture_sheet, sf::IntRect& texture_selector, 
		bool collision = false, int tile_type = 0);
	bool removeTile(const float& pos_x, const float& pos_y, const float& layer);
	void clearCurrentMap();
	void checkTileCollision(const float& dt, Entity* entity = NULL);

	/*** Renders ***/
	void Render(sf::RenderTarget& target, const sf::Sprite* entity = NULL);
	void deferredRender(sf::RenderTarget& target);
};



#endif