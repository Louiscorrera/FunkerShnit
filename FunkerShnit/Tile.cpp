#include "stdafx.h"
#include "Tile.h"



void Tile::initEnemySpawner(int enemyType, sf::Texture* enemyTexture)
{
	switch (enemyType)
	{
	case EnemyType::ENEMY1:
		this->enemySpawner = new EnemySpawner(*enemyTexture, sf::Vector2f(this->gridPosX * this->tileWidth, this->gridPosY * this->tileHeight), EnemyType::ENEMY1, 10, 0, 2); //Vampire 
		break;
	case EnemyType::ENEMY2:
		this->enemySpawner = new EnemySpawner(*enemyTexture, sf::Vector2f(this->gridPosX * this->tileWidth, this->gridPosY * this->tileHeight), EnemyType::ENEMY2, 10, 0, 1); //Mummy
	default:
		break;
	}
}

/* Tile constructor without a texture (Default) */
Tile::Tile(unsigned int grid_cord_x, unsigned int grid_cord_y, float tile_width, float tile_height)
	:gridPosX(grid_cord_x), gridPosY(grid_cord_y), tileWidth(tile_width), tileHeight(tile_height), collison(false), type(TileType::REGULAR), animationComponent(NULL)
{
	/* 
	* Init tile
	* - position: grid cordinate (X, Y) and multiplies each cordinate by the width and height of each tile
	* - size: width and height of each tile on tile map
	*/
	this->tileShape.setPosition(sf::Vector2f(static_cast<float>(this->gridPosX) * this->tileWidth, static_cast<float>(this->gridPosY) * this->tileHeight));
	this->tileShape.setSize(sf::Vector2f(this->tileWidth, this->tileHeight));

	/* For debugging purposes - Default tile colors */
	this->tileShape.setFillColor(sf::Color::White);
	this->tileShape.setOutlineThickness(1.f);
	this->tileShape.setOutlineColor(sf::Color::Black);

}

/* Tile constructor with a texture */
Tile::Tile(unsigned int grid_cord_x, unsigned int grid_cord_y, float tile_width, float tile_height, 
	const sf::Texture& tile_texture, const sf::IntRect& texture_selector, 
	bool collision, unsigned int type, 
	int enemy_type, sf::Texture* enemy_texture)
	:gridPosX(grid_cord_x), gridPosY(grid_cord_y), tileWidth(tile_width), tileHeight(tile_height), collison(collision), type(type), animationComponent(NULL), enemyType(enemy_type)
{


	/*
	* Init tile
	* - position: grid cordinate (X, Y) and multiplies each cordinate by the width and height of each tile
	* - size: width and height of each tile on tile map
	* - texture: texture sheet from editor state
	* - textureRect: texture rect selected from gui::textureSelector
	*/
	this->tileShape.setPosition(sf::Vector2f(static_cast<float>(this->gridPosX) * this->tileWidth, static_cast<float>(this->gridPosY) * this->tileHeight));
	this->tileShape.setSize(sf::Vector2f(this->tileWidth, this->tileHeight));
	this->tileShape.setTexture(&tile_texture);
	this->tileShape.setTextureRect(texture_selector);

	if (this->collison)
	{
		this->collisionBox.setPosition(sf::Vector2f(static_cast<float>(this->gridPosX) * this->tileWidth, static_cast<float>(this->gridPosY) * this->tileHeight));
		this->collisionBox.setSize(sf::Vector2f(this->tileWidth, this->tileHeight / 2));
		this->collisionBox.setFillColor(sf::Color(255, 0, 0, 120));
	}

	/* Checks if an enemy spawner is to be placed at this tile */

	if (enemyType >= 0)
	{
		if (enemy_texture) //Ensures no enemy spawners are initialized without an enemy texture sheet
		{
			this->initEnemySpawner(enemyType, enemy_texture);
			this->tileShape.setFillColor(sf::Color(255, 255, 255, 0));
		}
	}
	else
	{
		this->enemySpawner = NULL;
	}

}

Tile::~Tile()
{
}

const std::string Tile::getTileAsString() const
{
	std::stringstream ss;

	ss << this->gridPosX << " " << this->gridPosY << " " << this->tileWidth << " " << this->tileHeight << " " << this->tileShape.getTextureRect().left << " "
		<< this->tileShape.getTextureRect().top << " " << this->collison << " " << this->type << " " << this->enemyType;
	std::string something = ss.str();

	return something;
}

const sf::FloatRect& Tile::getTileGlobalBounds() const
{
	return this->collisionBox.getGlobalBounds();
}
const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->collisionBox.getGlobalBounds().intersects(bounds);
}

const bool& Tile::getCollision() const
{
	return this->collison;
}


void Tile::Update(sf::Texture& tile_texture)
{
}

void Tile::Render(sf::RenderTarget& target)
{
	if (this->enemyType >= 0) //If the type of tile is an enemy tile don't draw it
	{

	}
	else //The tile type is not an enemy, draw it!
	{
		target.draw(this->tileShape);
	}
	
	/* draw collision box */
	//target.draw(this->collisionBox);
}
