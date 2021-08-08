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
				delete this->tileMap[x][y][z];
				this->tileMap[x][y][z] = NULL;
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
	this->tileMap.resize(this->maxSizeX, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSizeX; x++)
	{
		for (size_t y = 0; y < this->maxSizeY; y++)
		{
			this->tileMap[x].resize(this->maxSizeY, std::vector<Tile*>());
			{
				for (size_t z = 0; z < this->maxLayers; z++)
				{
					this->tileMap[x][y].resize(this->maxLayers, NULL);
					//new Tile(x, y, this->gridSizeF, this->gridSizeF)
				}
			}
		}
	}
}

TileMap::TileMap(float max_size_x, float max_size_y, float max_layers, float grid_size_f)
	:maxSizeX(max_size_x), maxSizeY(max_size_y), maxLayers(max_layers), gridSizeF(grid_size_f)
{
	this->initTextures();
	this->initTileMap();
	this->overWriteEnabled = false;
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSizeX; x++)
	{
		for (size_t y = 0; y < this->maxSizeY; y++)
		{
				for (size_t z = 0; z < this->maxLayers; z++)
				{
					delete this->tileMap[x][y][z];
				}
		}
	}
	
}

void TileMap::toggleOverwrite()
{
	if (this->overWriteEnabled) { this->overWriteEnabled = false; }
	else { this->overWriteEnabled = true; }

}

const bool& TileMap::getOverWrite() const
{
	return this->overWriteEnabled;
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
	ofs << this->maxSizeX << " " << this->maxSizeY << " " << this->maxLayers << " " << this->gridSizeF << " " << "Resources/Images/Tiles/tilesheet2.png" << " ";

	/* Tile Specs */
	for (size_t x = 0; x < this->maxSizeX; x++)
	{
		for (size_t y = 0; y < this->maxSizeY; y++)
		{
			for (size_t z = 0; z < this->maxLayers; z++)
			{
				if(this->tileMap[x][y][z])
				ofs << z << " " << this->tileMap[x][y][z]->getTileAsString() << " ";
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
	*/

	/* Local Vars for readability */
	/* Tile Map locals */
	std::string texture_sheet_file = "";
	/* Tile Locals */
	unsigned int layer(0), grid_cord_x(0), grid_cord_y(0);
	float tile_width(0), tile_height(0);
	int texture_rect_left(0), texture_rect_top(0);
	sf::IntRect rect;

	/* Init tile map before initTileMap(string) to ensure the correct texture sheet is loaded, as well as all the other tile map dimensions */
	ifs >> this->maxSizeX >> this->maxSizeY >> this->maxLayers >> this->gridSizeF >> texture_sheet_file;

	this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet2.png");

	this->initTileMap();

	rect.width = this->gridSizeF;
	rect.height = this->gridSizeF;

	while (ifs >> layer >> grid_cord_x >> grid_cord_y >> tile_width >> tile_height >> texture_rect_left >> texture_rect_top)
	{
		rect.left = texture_rect_left;
		rect.top = texture_rect_top;
		this->tileMap[grid_cord_x][grid_cord_y][layer] = new Tile(grid_cord_x, grid_cord_y, tile_width, tile_height, this->tileTextureSheet, rect);
	}
	
	
	

	ifs.close();
}

void TileMap::Update()
{
}

bool TileMap::addTile(const unsigned int& pos_x, const unsigned int& pos_y, const float& layer, sf::Texture& tile_texture_sheet, sf::IntRect& texture_selector)
{

	if (pos_x < this->maxSizeX && pos_x >= 0
		&& pos_y < this->maxSizeY && pos_y >= 0
		&& layer < this->maxLayers && layer >= 0)
	{
		/* Tile layer is empty and texture can be added to this tile */
		if (this->tileMap[pos_x][pos_y][layer] == NULL || this->overWriteEnabled)
		{
			this->tileMap[pos_x][pos_y][layer] = new Tile(pos_x, pos_y, this->gridSizeF, this->gridSizeF, tile_texture_sheet, texture_selector);
			return true;
		}
		else
		{
			return false;
		}
	}

}

bool TileMap::removeTile(const float& pos_x, const float& pos_y, const float& layer)
{
	if (pos_x < this->maxSizeX && pos_x >= 0
		&& pos_y < this->maxSizeY && pos_y >= 0
		&& layer < this->maxLayers && layer >= 0)
	{
		if (this->tileMap[pos_x][pos_y][layer] != NULL)
		{
			this->tileMap[pos_x][pos_y][layer] = NULL;
			std::cout << "Deleted Tile\n";
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

void TileMap::Render(sf::RenderTarget& target)
{
	for (auto& x : this->tileMap)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != NULL)
				{
					z->Render(target);
				} 
			}
		}
	}
}

