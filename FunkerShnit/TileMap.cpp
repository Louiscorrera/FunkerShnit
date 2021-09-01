#include "stdafx.h"
#include "TileMap.h"

void TileMap::initTextures()
{

	if (!this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.2.png"))
	{
		std::cout << "ERROR:InitTextures()::TILEMAP Could not load tile texture sheet from file\n";
	}

	this->textureFileNames[EnemyType::ENEMY1] = "Resources/Images/Sprites/Enemy/ArmyEnemy.png"; //Add these in!!!

	this->textureFileNames[EnemyType::ENEMY2] = "";

	this->textureFileNames[EnemyType::ENEMY3] = "";

	//for (int i = EnemyType::ENEMY1; i < EnemyType::ENEMY3; i++)
	//{
		if (!this->enemyTextures[EnemyType::ENEMY1].loadFromFile(this->textureFileNames[EnemyType::ENEMY1]))
		{
			std::cout << "ERROR::InitTextures()::TILEMAP could not load one or more of the enemytextures\n";
		}
	//}

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

	this->initTextures();

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

void TileMap::initVars()
{
	this->collisionEnabled = false;
	this->collisionType = CollisionType::COVER;
	this->maxTiles = 10; 
	this->tileType = TileType::REGULAR; 
	this->enemySpawnerEnabled = false;
	this->enemyType = EnemyType::ENEMY1;
}

TileMap::TileMap(float max_size_x, float max_size_y, float max_layers, float grid_size_f)
	:maxSizeX(max_size_x), maxSizeY(max_size_y), maxLayers(max_layers), gridSizeF(grid_size_f)
{
	this->initVars();
	this->initTextures();
	this->initTileMap();
	
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


void TileMap::toggleCollision()
{
	this->collisionEnabled = !this->collisionEnabled;
}

void TileMap::toggleType()
{
	/* If toggling and type is Enemy reset type to Default = 0 */
	if (this->tileType == TileType::ENEMY)
	{
		this->tileType = TileType::REGULAR;
		/* No longer Enemy type and disable enemy spawner enabling feature */
		this->enemySpawnerEnabled = false;
	}
	else
	{
		tileType++;
	}

	/* Check, at the end of the type toggle, if the type is enemy. Enable member enemySpawnerEnabled to true */
	if (this->tileType == TileType::ENEMY)
	{
		this->enemySpawnerEnabled = true;
	}
}

void TileMap::toggleEnemySpawner()
{
	this->enemySpawnerEnabled = !this->enemySpawnerEnabled;
}

void TileMap::toggleEnemyType()
{
	
	if (this->enemySpawnerEnabled)
	{
		if (this->enemyType == EnemyType::ENEMY3)
		{
			this->enemyType = EnemyType::ENEMY1;
		}
		else
		{
			enemyType++;
		}
	}
	else
	{
		std::cout << "Could not toggle enemy type as tile type is not ENEMY\n";
	}

	
}

void TileMap::toggleCollistionType()
{
	if(this->collisionEnabled)
	{
		if (this->collisionType == CollisionType::RIGHT)
		{
			this->collisionType = CollisionType::COVER;
		}
		else
		{
			this->collisionType++;
		}
	}
	else
	{
		std::cout << "Could not toggle enemy type as tile type is collision\n";
	}
}


const bool& TileMap::getCollision() const
{
	return this->collisionEnabled;
}

const bool& TileMap::getEnemySpawner() const
{
	return this->enemySpawnerEnabled;
}

const int& TileMap::getEnemyType() const
{
	return this->enemyType;
}

const int& TileMap::getTileType() const
{
	return this->tileType;
}

const int& TileMap::getCollisionType() const
{
	return this->collisionType;
}

const sf::Vector2f& TileMap::getTileMapMaxSize()
{
	return sf::Vector2f(this->maxSizeX * this->gridSizeF, this->maxSizeY * this->gridSizeF);
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
	ofs << this->maxSizeX << " " << this->maxSizeY << " " << this->maxLayers << " " << this->gridSizeF << " " << "Resources/Images/Tiles/tilesheet1.2.png" << " ";


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
	bool collision(false);
	int collision_type(0), tile_type(0), enemy_type(0);
	
	

	/* Init tile map before initTileMap(string) to ensure the correct texture sheet is loaded, as well as all the other tile map dimensions */
	ifs >> this->maxSizeX >> this->maxSizeY >> this->maxLayers >> this->gridSizeF >> texture_sheet_file;

	this->tileTextureSheet.loadFromFile(texture_sheet_file);

	this->initTileMap();

	rect.width = this->gridSizeF;
	rect.height = this->gridSizeF;

	while (ifs >> layer >> grid_cord_x >> grid_cord_y >> tile_width >> tile_height >> texture_rect_left >> texture_rect_top >> collision >> collision_type >> tile_type >> enemy_type)
	{
		rect.left = texture_rect_left;
		rect.top = texture_rect_top;
		if (enemy_type >= 0)
		{
			this->tileMap[grid_cord_x][grid_cord_y][layer].push_back(new Tile(grid_cord_x, grid_cord_y, tile_width, tile_height, 
				this->tileTextureSheet, rect, 
				collision, collision_type, 
				tile_type, enemy_type, &this->enemyTextures[enemy_type]));
		}
		else
		{
			this->tileMap[grid_cord_x][grid_cord_y][layer].push_back(new Tile(grid_cord_x, grid_cord_y, tile_width, tile_height, 
				this->tileTextureSheet, rect, 
				collision, collision_type, tile_type));
		}
	}
	
	
	

	ifs.close();
}

void TileMap::Update()
{

}

bool TileMap::addTile(const unsigned int& pos_x, const unsigned int& pos_y, const float& layer, 
	sf::Texture& tile_texture_sheet, sf::IntRect& texture_selector, 
	bool collision, int collision_type,
	int tile_type)
{
	/* Check if grid position is in the tile map & a valid position */
	if (pos_x < this->maxSizeX && pos_x >= 0
		&& pos_y < this->maxSizeY && pos_y >= 0
		&& layer < this->maxLayers && layer >= 0)
	{
			
		/* Check if enemy spawner is enabled */
		if (this->enemySpawnerEnabled)
		{
			
			switch (this->enemyType)
			{
			case EnemyType::ENEMY1:
				this->tileMap[pos_x][pos_y][layer].push_back(new Tile(pos_x, pos_y, this->gridSizeF, this->gridSizeF, tile_texture_sheet, texture_selector, collision, collision_type, tile_type, 
					this->enemyType, &this->enemyTextures[EnemyType::ENEMY1]));
				std::cout << "Added Enemy Spawner!!!\n";
				break;
			case EnemyType::ENEMY2:
				this->tileMap[pos_x][pos_y][layer].push_back(new Tile(pos_x, pos_y, this->gridSizeF, this->gridSizeF, tile_texture_sheet, texture_selector, collision, collision_type, tile_type,
					this->enemyType, &this->enemyTextures[EnemyType::ENEMY2]));
				std::cout << "Added Enemy Spawner!!!\n";
				break;
			case EnemyType::ENEMY3:
				this->tileMap[pos_x][pos_y][layer].push_back(new Tile(pos_x, pos_y, this->gridSizeF, this->gridSizeF, tile_texture_sheet, texture_selector, collision, collision_type, tile_type,
					this->enemyType, &this->enemyTextures[EnemyType::ENEMY3]));
				std::cout << "Added Enemy Spawner3!!!\n";
				break;
			default:
				break;
			}
		}
		else
		{
			this->tileMap[pos_x][pos_y][layer].push_back(new Tile(pos_x, pos_y, this->gridSizeF, this->gridSizeF, tile_texture_sheet, texture_selector, collision, collision_type, tile_type));

		}
			
			return true;
		
	}
	else
	{
		return false;
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
	

	/* Check for collision with map boundary */

	/* Left Map boundary */
	if (entity->getEntityGlobalBounds().left < 0)
	{
		entity->stopVelocityX();
		entity->setPosition(0, entity->getPosition().y);
	}
	/* Right Map boundary */
	else if (entity->getEntityGlobalBounds().left + entity->getEntityGlobalBounds().width > this->maxSizeX * this->gridSizeF)
	{
		entity->stopVelocityX();
		entity->setPosition(this->maxSizeX * this->gridSizeF - entity->getEntityGlobalBounds().width, entity->getPosition().y);
	}
	/* Top Map Boundary */
	else if (entity->getEntityGlobalBounds().top < 0)
	{
		entity->stopVelocityY();
		entity->setPosition(entity->getPosition().x, 0.f);
	}
	/* Bottom Map Boundary */
	else if (entity->getEntityGlobalBounds().top + entity->getEntityGlobalBounds().height > this->maxSizeY * this->gridSizeF)
	{
		entity->stopVelocityY();
		entity->setPosition(entity->getPosition().x, this->maxSizeY * this->gridSizeF - entity->getEntityGlobalBounds().height);
	}

	/* Check if there is an entity(default = NULL), Render around that entity if it exists */
	if (entity)
	{
		/* Local vars to store distance from entity to render */
		int startX(0), endX(0), startY(0), endY(0), layer(0);

		/* Set and update the the offset from the entity to render around */
		startX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) - 5;
		if (startX < 0) { startX = 0; }
		if (endX > this->maxSizeX) { endX = this->maxSizeX; }

		endX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) + 5;
		if (endX > this->maxSizeX) { endX = this->maxSizeX; }

		startY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) - 5;
		if (startY < 0) { startY = 0; }

		endY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) + 5;
		if (endY < 0) { endY = 0; }
		if (endY > this->maxSizeY) { endY = this->maxSizeY - 1; }

		

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
								entity->stopVelocityY();
								entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height + 0.5); //Make this function in entity
							}
							//Top collision
							else if (playerBounds.top < wallBounds.top
								&& playerBounds.left < wallBounds.left + wallBounds.width
								&& playerBounds.left + playerBounds.width > wallBounds.left
								&& playerBounds.top + playerBounds.height <= wallBounds.top)
							{
								entity->stopVelocityY(); //Make this function in entity
								entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height); 
								
							}
							else {}


							//Right Collison
							if (playerBounds.left < wallBounds.left
								&& playerBounds.left + playerBounds.width <= wallBounds.left
								&& playerBounds.top < wallBounds.top + wallBounds.height
								&& playerBounds.top + playerBounds.height > wallBounds.top)
							{
 								entity->stopVelocity(); //Make this function in entity
								entity->setPosition(wallBounds.left - playerBounds.width - 0.3, playerBounds.top); //Make this function in entity
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

void TileMap::checkEnemySpawners(const float& dt, std::vector<Enemy*>* game_enemies, Entity* entity)
{

	/* Local vars to store distance from entity to render */
	int startX(0), endX(0), startY(0), endY(0), layer(0);

	/* Set and update the the offset from the entity to render around */
	startX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) - 5;
	if (startX < 0) { startX = 0; }
	if (endX > this->maxSizeX) { endX = this->maxSizeX; }

	endX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) + 5;
	if (endX > this->maxSizeX) { endX = this->maxSizeX; }

	startY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) - 5;
	if (startY < 0) { startY = 0; }

	endY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) + 5;
	if (endY < 0) { endY = 0; }
	if (endY > this->maxSizeY) { endY = this->maxSizeY - 1; }



	for (size_t x = startX; x < endX; x++)
	{
		for (size_t y = startY; y < endY; y++)
		{
			for (size_t k = 0; k < this->tileMap[x][y][layer].size(); k++)
			{
				if (this->tileMap[x][y][layer][k]) /* if the tile is not null */
				{
					if (this->tileMap[x][y][layer][k]->enemySpawner) /* IF the tile has a valid enemy spawner */
					{
						/* Attempt to spawn */ 
						/* If spawnenemy returns NULL */
						//Do Nothing
						if (this->tileMap[x][y][layer][k]->enemySpawner->getIsFull())
						{

						}
						else
						{
							/* If the spawner is not active, activate spawner */
							if (!this->tileMap[x][y][layer][k]->enemySpawner->getSpawnerActive())
							{
								this->tileMap[x][y][layer][k]->enemySpawner->toggleSpawnerActive();
							}

							if (this->tileMap[x][y][layer][k]->enemySpawner->getEnemySpawnTimer())
							{
								/* Add new enemy back to gamestate's enemy array */
								game_enemies->push_back(this->tileMap[x][y][layer][k]->enemySpawner->spawnEnemy());
							}

						}
						/* Update spawner */
						
						this->tileMap[x][y][layer][k]->enemySpawner->Update(dt); /* Update the spawner */

					}else{}
				}else{}
			}
		}
	}

}

void TileMap::Render(sf::RenderTarget& target, const sf::Sprite* entity, sf::View* mainView)
{
	/* Check if there is an entity(default = NULL), Render around that entity if it exists */
	if (entity)
	{
		/* Local vars to store distance from entity to render */
		int startX(0), endX(0), startY(0), endY(0), layer(0);



		/* Set and update the the offset from the entity to render around */
		startX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) - 25;
		if (startX < 0) { startX = 0; }
		if (endX > this->maxSizeX) { endX = this->maxSizeX; }

		endX = static_cast<int>((entity->getPosition().x) / this->gridSizeF) + 25;
		if (endX > this->maxSizeX) { endX = this->maxSizeX; }

		startY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) - 25;
		if (startY < 0) { startY = 0; }

		endY = static_cast<int>((entity->getPosition().y) / this->gridSizeF) + 25;
		//if (endY < 0) { endY = 0; }
		if (endY > this->maxSizeY) { endY = this->maxSizeY; }

		

			for (size_t x = startX; x < endX; x++)
			{
				for (size_t y = startY; y < endY; y++)
				{
					for (size_t k = 0; k < this->tileMap[x][y][layer].size(); k++)
					{
						/* If this tile exists render it */
						if (this->tileMap[x][y][layer][k]->type == TileType::DEFERRED)
						{
							this->deferredRenderStack.push(this->tileMap[x][y][layer][k]);
						}
						else
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

void TileMap::deferredRender(sf::RenderTarget& target)
{
	while (!this->deferredRenderStack.empty())
	{
		this->deferredRenderStack.top()->Render(target);
		this->deferredRenderStack.pop();
	}
	
}

