#pragma once


class HitboxComponent
{

	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;

	

public:

	float offsetX;
	float offsetY;

	float OffsetGridX;
	float offsetGridY;

	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, bool special = false);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& frect);
	const sf::FloatRect getHitboxGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
	const sf::Vector2f& getPosition();

	void update();
	void setPosition(const sf::Vector2f& position);
	void setRotation(float rotation);

	void render(sf::RenderTarget& target);
};

