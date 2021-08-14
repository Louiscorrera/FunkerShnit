#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H


enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
class MovementComponent
{
private:
	/**** DATA MEMBERS ****/

	/* Entity */
	sf::Sprite& entity;

	/* Velocity */
	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;


	/**** METHODS(Private) ****/

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	MovementComponent(sf::Sprite& sprite, float maxVelocit, float acceleration, float deceleration);
	virtual ~MovementComponent();

	/**** ACCESSORS ****/
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	const bool getState(const short unsigned state) const;

	/**** METHODS ****/

	/*** Updates ***/
	void Update(const float& dt);
	void move(const float dir_x, const float dir_y, const float& dt);

	/*** Renders ***/
};


#endif // !MOVEMENTCOMPONENT_H
