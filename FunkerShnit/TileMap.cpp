#include "stdafx.h"
#include "TileMap.h"

void TileMap::initTextures()
{

	if (!this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet2.png"))
	{
		std::cout << "ERROR:InitTextures()::TILEMAP Could not load tile texture sheet from file\n";
	}
}

void TileMap::clearMap()
{
	for (size_t x = 0; x < this->maxSizeX; x++)
	{
		for (size_t y = 0; y < this->maxSizeY; y++)
		{
			for (size_t z = 0; z < this->maxLayers; z++)
			{
				for (size_t k = 0; k < this->tileMap[x][y][z].size(); k++)
				{
					delete this->tileMap[x][y][z][k];
					this->tileMap[x][y][z].pop_back();
				}
			}
			this->tileMap[x][y].clear();
		}
		this->tileMap[x].clear();
	}
	this->tileMap.clear();
}

void TileMap::initTileMap(std::string texture_sheet_file)
{

	/*if (!this->tileTextureSheet.loadFromFile(texture_sheet_file))
	{
		std::cout << "ERROR:InitTextures()::TILEMAP Could not load tile texture sheet from file\n";
	}*/

	/* Creating an empty TileMap w/default tile settings (Red fill & green outline) */
	this->tileMap.resize(this->maxSizeX, std::vector<std::vector < std::vector <Tile*>>>());
	for (size_t x = 0; x < this->maxSizeX; x++)
	{
		for (size_t y = 0; y < this->maxSizeY; y++)
		{
			this->tileMap[x].resize(this->maxSizeY, std::vector<std::vector<Tile*>>());
			{
				for (size_t z = 0; z < this->maxLayers; z++)
				{
					this->tileMap[x][y].resize(this->maxLayers, std::vector<Tile*>());
					//new Tile(x, y, this->gridSizeF, this->gridSizeF)
					for (size_t k = 0; k < this->tileMap[x][y][z].size(); k++)
					{
						this->tileMap[x][y][z].resize(this->maxTiles, NULL);
					}
				}
			}
		}
	}
}

TileMap::TileMap(float max_size_x, float max_size_y, float max_layers, float grid_size_f)
	:maxSizeX(max_size_x), maxSizeY(max_size_y), maxLayers(max_layers), gridSizeF(grid_size_f), collisionEnabled(false)
{
	this->initTextures();
	this->initTileMap();
	this->overWriteEnabled = false;
	this->maxTiles = 10;
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSizeX; x++)
	{
		for (size_t y = 0; y < this->maxSizeY; y++)
		{
				for (size_t z = 0; z < this->maxLayers; z++)
				{
					for (size_t k = 0; k < this->tileMap[x][y][z].size(); k++)
					{
						delete this->tileMap[x][y][z][k];
						this->tileMap[x][y][z].pop_back();
					}
				}
		}
	}
	
}

void TileMap::toggleOverwrite()
{
	if (this->overWriteEnabled) { this->overWriteEnabled = false; }
	else { this->overWriteEnabled = true; }

}

void TileMap::toggleCollision()
{
	this->collisionEnabled = !this->collisionEnabled;
}

const bool& TileMap::getOverWrite() const
{
	return this->overWriteEnabled;
}

const bool& TileMap::getCollision() const
{
	return this->collisionEnabled;
}

void TileMap::saveTileMap(std::string filename)
{
	std::ofstream ofs(filename);
	if (!ofs.is_open()) { throw "ERROR::saveTileMap()::TILEMAP could not open file to save tile map to"; return; }

	/* Saving TileMap Specs 
	* - float -- Max Size X
	* - float -- Max Size Y
	* - float -- Max Layers
	* - float -- Grid Size
	* - string -- texture sheet file name
	* 
	* Saving Tile Specs
	* - uint -- Grid Coordinate X
	* - uint -- Grid Coordinate Y
	* - float -- Tile Width
	* - float -- Tile Height
	* - int -- Texture Rectangle Left
	* - int -- Texture Rectangle Top
	* 
	*/

	/* TileMap Specs */
	ofs << this->maxSizeX << " " << this->maxSizeY << " " << this->maxLayers << " " << this->gridSizeF << " " << "Resources/Images/Tiles/grassandtilesheet.png" << " ";

	/* Tile Specs */
	for (size_t x = 0; x < this->maxSizeX; x++)
	{
		for (size_t y = 0; y < this->maxSizeY; y++)
		{
			for (size_t z = 0; z < this->maxLayers; z++)
			{
				if (!this->tileMap[x][y][z].empty())
				{
					for (size_t k = 0; k < this->tileMap[x][y][z].size(); k++)
					{
						if (this->tileMap[x][y][z][k])
							ofs << z << " " << this->tileMap[x][y][z][k]->getTileAsString() << " ";
					}
				}
			}
		}
	}


	ofs.close();

}

void TileMap::loadTileMap(std::string filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open()) { throw "ERROR::loadTileMap()::TILEMAP could not load saved tile map from file "; }

	/* Clear current tile map and then init a new empty tile map */
	this->clearMap();

	/* 
	* Loading TileMap Specs
	* - float -- Max Size X
	* - float -- Max Size Y
	* - float -- Max Layers
	* - float -- Grid Size
	* - string -- texture sheet file name
	*
	* Loading Tile Specs
	* - uint -- Layer
	* - uint -- Grid Coordinate X
	* - uint -- Grid Coordinate Y
	* - float -- Tile Width
	* - float -- Tile Height
	* - int -- Texture Rectangle Left
	* - int -- Texture Rectangle Top
	* - bool -- Collision
	*/

	/* Local Vars for readability */
	/* Tile Map locals */
	std::string texture_sheet_file = "";
	/* Tile Locals */
	unsigned int layer(0), grid_cord_x(0), grid_cord_y(0);
	float tile_width(0), tile_height(0);
	int texture_rect_left(0), texture_rect_top(0);
	sf::IntRect rect;
	bool collision = false;

	/* Init tile map before initTileMap(string) to ensure the correct texture sheet is loaded, as well as all the other tile map dimensions */
	ifs >> this->maxSizeX >> this->maxSizeY >> this->maxLayers >> this->gridSizeF >> texture_sheet_file;

	this->tileTextureSheet.loadFromFile(texture_sheet_file);

	this->initTileMap();

	rect.width = this->gridSizeF;
	rect.height = this->gridSizeF;

	while (ifs >> layer >> grid_cord_x >> grid_cord_y >> tile_width >> tile_height >> texture_rect_left >> texture_rect_top >> collision)
	{
		rect.left = texture_rect_left;
		rect.top = texture_rect_top;
		this->tileMap[grid_cord_x][grid_cord_y][layer].push_back (new Tile(grid_cord_x, grid_cord_y, tile_width, tile_height, this->tileTextureSheet, rect, collision));
	}
	
	
	

	ifs.close();
}

void TileMap::Update()
{

}

bool TileMap::addTile(const unsigned int& pos_x, const unsigned int& pos_y, const float& layer, sf::Texture& tile_texture_sheet, sf::IntRect& texture_selector, bool collision)
{

	if (pos_x < this->maxSizeX && pos_x >= 0
		&& pos_y < this->maxSizeY && pos_y >= 0
		&& layer < this->maxLayers && layer >= 0)
	{
		/* Tile layer is empty and texture can be added to this tile */
		
			if (this->collisionEnabled)
			{
				this->tileMap[pos_x][pos_y][layer].push_back(new Tile(pos_x, pos_y, this->gridSizeF, this->gridSizeF, tile_texture_sheet, texture_selector, collision));
			}
			else
			{
				this->tileMap[pos_x][pos_y][layer].push_back(new Tile(pos_x, pos_y, this->gridSizeF, this->gridSizeF, tile_texture_sheet, texture_selector));
			}
			return true;
		
	}

}

bool TileMap::removeTile(const float& pos_x, const float& pos_y, const float& layer)
{
	if (pos_x < this->maxSizeX && pos_x >= 0
		&& pos_y < this->maxSizeY && pos_y >= 0
		&& layer < this->maxLayers && layer >= 0)
	{
		if (!this->tileMap[pos_x][pos_y][layer].empty())
		{
			delete this->tileMap[pos_x][pos_y][layer][this->tileMap[pos_x][pos_y][layer].size()-1];
			this->tileMap[pos_x][pos_y][layer].pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}
}

void TileMap::clearCurrentMap()
{
	this->clearMap();
	this->initTileMap();
}

void TileMap::checkTileCollision(const float& dt, Entity* entity)
{
	/* Check if there is an entity(default = NULL), Render around that entity if it exists */
	if (entity)
	{
		/* Local vars to store distance from entity to render */
		int startX(0), endX(0), startY(0), endY(0), layer(0);

		/* Set and update the the offset from the entity to render around */
		startX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) - 10;
		if (startX < 0) { startX = 0; }
		endX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) + 10;
		if (endX < 0) { endX = 0; }
		startY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) - 10;
		if (startY < 0) { startY = 0; }
		endY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) + 10;
		if (endY < 0) { endY = 0; }

	

		for (size_t x = startX; x < endX; x++)
		{
			for (size_t y = startY; y < endY; y++)
			{
				for (size_t k = 0; k < this->tileMap[x][y][layer].size(); k++)
				{
					if (this->tileMap[x][y][layer][k] == NULL)
					{
					}
					else
					{
						sf::FloatRect playerBounds = entity->getEntityGlobalBounds();
						sf::FloatRect wallBounds = this->tileMap[x][y][layer][k]->getTileGlobalBounds();
						sf::FloatRect playerNextBounds = entity->getEntityNextBounds(dt);

						/*system("cls");
						std::cout << playerBounds.left << " " << playerBounds.top << "\n";
						std::cout << playerNextBounds.left << " " << playerNextBounds.top << "\n";*/

						/* If this tile exists render it */
						if (this->tileMap[x][y][layer][k]->getCollision() == true && this->tileMap[x][y][layer][k]->intersects(playerNextBounds) == true)
						{
							//Bottom Collision
							if (playerBounds.top > wallBounds.top
								&& playerBounds.left < wallBounds.left + wallBounds.width
								&& playerBounds.left + playerBounds.width > wallBounds.left
								&& playerBounds.top > wallBounds.top + wallBounds.height)
							{
								entity->stopVelocityY(); //Make this function in entity
								entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height + .5); //Make this function in entity
							}
							//Top collision
							else if (playerBounds.top < wallBounds.top
								&& playerBounds.left < wallBounds.left + wallBounds.width
								&& playerBounds.left + playerBounds.width > wallBounds.left
								&& playerBounds.top + playerBounds.height < wallBounds.top)
							{
								entity->stopVelocityY(); //Make this function in entity
								entity->setPosition(playerBounds.left, wallBounds.top - wallBounds.height + 3); //Make this function in entity
							}
							else {}


							//Right Collison
							if (playerBounds.left < wallBounds.left
								&& playerBounds.left + playerBounds.width < wallBounds.left
								&& playerBounds.top < wallBounds.top + wallBounds.height
								&& playerBounds.top + playerBounds.height > wallBounds.top)
							{
								entity->stopVelocity(); //Make this function in entity
								entity->setPosition(wallBounds.left - wallBounds.width + entity->getHitboxOffsetX() - 0.5, playerBounds.top); //Make this function in entity
							}
							//Left Collision
							else if (playerBounds.left > wallBounds.left
								&& playerBounds.left > wallBounds.left + wallBounds.width
								&& playerBounds.top < wallBounds.top + wallBounds.height
								&& playerBounds.top + playerBounds.height > wallBounds.top)
							{
								entity->stopVelocityX(); //Make this function in entity
								entity->setPosition(wallBounds.left + wallBounds.width + .5, playerBounds.top); //Make this function in entity
							}
							else {}

						}
						else {}
					}
				}
			}
		}
	}
	else
	{
		//No entity
	}
}

void TileMap::Render(sf::RenderTarget& target, const sf::Sprite* entity)
{
	/* Check if there is an entity(default = NULL), Render around that entity if it exists */
	if (entity)
	{
		/* Local vars to store distance from entity to render */
		int startX(0), endX(0), startY(0), endY(0), layer(0);

		/* Set and update the the offset from the entity to render around */
		startX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) - 15;
		if (startX < 0) { startX = 0; }
		endX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) + 15;
		if (endX < 0) { endX = 0; }
		startY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) - 15;
		if (startY < 0) { startY = 0; }
		endY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) + 15;
		if (endY < 0) { endY = 0; }


		for (size_t x = startX; x < endX; x++)
		{
			for (size_t y = startY; y < endY; y++)
			{
				for (size_t k = 0; k < this->tileMap[x][y][layer].size(); k++)
				{
					/* If this tile exists render it */
					if (this->tileMap[x][y][layer][k])
					{
						this->tileMap[x][y][layer][k]->Render(target);
					}
				}
			}
		}
	}
	else /* If there is no entity render the whole map */
	{
		for (auto& x : this->tileMap)
		{
			for (auto& y : x)
			{
				for (auto& z : y)
				{
					for (auto* k : z)
					if (k != NULL)
					{
						k->Render(target);
					}
				}
			}
		}
	}
}

