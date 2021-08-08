#include "stdafx.h"
#include "Tile.h"



/* Tile constructor without a texture (Default) */
Tile::Tile(unsigned int grid_cord_x, unsigned int grid_cord_y, float tile_width, float tile_height)
	:gridPosX(grid_cord_x), gridPosY(grid_cord_y), tileWidth(tile_width), tileHeight(tile_height)
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
Tile::Tile(unsigned int grid_cord_x, unsigned int grid_cord_y, float tile_width, float tile_height, const sf::Texture& tile_texture, const sf::IntRect& texture_selector)
	:gridPosX(grid_cord_x), gridPosY(grid_cord_y), tileWidth(tile_width), tileHeight(tile_height)
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

	
}

Tile::~Tile()
{
}

const std::string Tile::getTileAsString() const
{
	std::stringstream ss;

	ss << this->gridPosX << " " << this->gridPosY << " " << this->tileWidth << " " << this->tileHeight << " " << this->tileShape.getTextureRect().left << " " << this->tileShape.getTextureRect().top;
	std::string something = ss.str();

	return something;
}

void Tile::Update(sf::Texture& tile_texture)
{
}

void Tile::Render(sf::RenderTarget& target)
{
	target.draw(this->tileShape);
}
