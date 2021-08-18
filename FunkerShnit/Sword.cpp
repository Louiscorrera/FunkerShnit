#include "stdafx.h"
#include "Sword.h"

void Sword::initTexture()
{
	//TODO
	/* Set the texture rect to the part of the texture that is the sword */

	/* Init origin of sword to center */
	this->item.setOrigin(this->item.getGlobalBounds().width / 2.f, this->item.getGlobalBounds().height / 2.f);
}

void Sword::initVars()
{
	this->isEquipped = false;
	this->isAttacking = false;

	this->swordAttack = SwordAttack::DEFAULT;
	this->swingVelocity.x = 30.f;
	this->swingVelocity.y = 30.f;

	this->attackTimer = 0.f;
	this->attackTimerReset = 50.f;

	this->mousePosWindow.x = 0;
	this->mousePosWindow.y = 0;
}

Sword::Sword(std::string item_name, unsigned int item_level, unsigned int item_value, unsigned int item_weight, 
	bool item_wieldable, bool item_consumable, 
	sf::Texture& item_texture)
	:Weapon(item_name, item_level, item_value, item_weight, item_wieldable, item_consumable, item_texture), swordHitboxComponent(NULL) 
{
	this->initTexture();
	this->initVars();

	/* Set Entity and Sword Range Bounds */
	this->swordBounds = sf::FloatRect(this->entityBounds.left, this->entityBounds.top, this->entityBounds.width * 2, this->entityBounds.height * 2);
}

Sword::~Sword() 
{
	delete this->swordHitboxComponent;
}

const bool& Sword::getSwordEquipped() const
{
	return this->isEquipped;
}

const bool& Sword::getSwordState() const
{
	return this->isAttacking;
}

const bool& Sword::getAttackTimer()
{
	if (this->attackTimer >= this->attackTimerReset)
	{
		this->attackTimer = 0.f;
		return true;
	}
	return false;
}

void Sword::toggleEquip()
{
	/* Used outside sword to toggle if a sword object is equipped or not */
	if (this->wieldable)
	{
		this->isEquipped = !this->isEquipped;
	}
}

void Sword::toggleAttacking()
{
	this->isAttacking = !this->isAttacking;
}

void Sword::Update(const float& dt, const sf::Vector2i mouse_pos_window)
{
	if (this->isEquipped) /* Sword is equipped */
	{
		/* Do sword stuff */
		this->updateAttackTimer(dt);
		this->updateMousePos(mouse_pos_window);
		
	}
	else
	{
		/* Sword is not equipped, don't do sword stuff */
	}

}

void Sword::updateMousePos(sf::Vector2i mouse_pos_window)
{
	this->mousePosWindow.x = mouse_pos_window.x;
	this->mousePosWindow.y = mouse_pos_window.y;
}




void Sword::updateSwordAttack(int sword_attack)
{
	this->swordAttack = sword_attack;

	if (this->isAttacking)
	{
		switch (this->swordAttack)
		{
		case SwordAttack::DEFAULT:
			this->swingVelocity.x = 40.f;
			this->swingVelocity.y = 40.f;

			break;
		case SwordAttack::STAB:
			this->swingVelocity.x = 50.f;
			this->swingVelocity.y = 50.f;

			break;
		case SwordAttack::SLASH:
			this->swingVelocity.x = 40.f;
			this->swingVelocity.y = 40.f;

			break;
		case SwordAttack::CRUSH:
			this->swingVelocity.x = 20.f;
			this->swingVelocity.y = 20.f;

			break;
		default:
			throw "ERROR::SWORD::UpdateSwordState(int) invalid sword state enum";
			break;
		}
	}
	/* Based off what num is passed in update the sword to that state*/
}

void Sword::updateAttackTimer(const float& dt)
{
	if (this->attackTimer < this->attackTimerReset)
	{
		this->attackTimer += 100.f * dt;
	}
}

void Sword::updateSwordRanges(sf::FloatRect playerBounds)
{
	
	this->entityBounds = playerBounds;
	this->swordBounds = sf::FloatRect(this->entityBounds.left - 50, this->entityBounds.top - 50, this->entityBounds.width * 4, this->entityBounds.height * 3);
}

void Sword::animateSword(sf::FloatRect playerBounds)
{
	/* Find the center of the entity to do animations around */
	float middleOfEntity = playerBounds.width / 2.f;

	/* Update the sword range boxes */
	this->updateSwordRanges(playerBounds);

	/* Animate swords attack based on current state  */
	if (this->isEquipped) //If the sword is equipped
	{
		
		if (this->isAttacking) //If the sword is attacking check which attack state the sword is in and animate accordingly
		{
			switch (this->swordAttack)
			{
			case SwordAttack::DEFAULT:
				this->rotateSword(playerBounds);

				break;
			case SwordAttack::STAB:


				break;
			case SwordAttack::SLASH:


				break;
			case SwordAttack::CRUSH:


				break;
			default:
				throw "ERROR::SWORD::UpdateSwordState(int) invalid sword state enum";
				break;
			}
		}
		else //If the sword is equipped but not attacking play idle state animation i.e floating
		{
			/* This should be the sword floating around */
			//this->rotateSword(playerBounds); //This needs to go into default attack branch above, keeping now until attack system is implemented
			this->floatSword();
		}
	}
	else {} /* Sword is not equipped */
}\


void Sword::rotateSword(sf::FloatRect playerBounds)
{
	/* Get sword's current position (origin at center) */
	sf::Vector2f curPos = this->item.getPosition();
	/* Get player's current position */
	sf::Vector2f playerPos = sf::Vector2f(playerBounds.left + (playerBounds.width /2.f), playerBounds.top + (playerBounds.height / 2.f));
	
	//Debug
	//std::cout << "Player left: " << playerPos.x << " Player top: " << playerPos.y << "\n";

	/* Create a ray from center of player to mouse position (relative to view) */
	sf::Vertex vertices[2];
	vertices[0].position = sf::Vector2f(playerPos.x, playerPos.y);
	vertices[1].position = sf::Vector2f(this->mousePosWindow.x, this->mousePosWindow.y);

	/* MMMM pie! */
	const float PI = 3.14159265;

	
	/* Calculate the X side length and Y side length of the right triangle formed from sword position to mouse position */
	float dx = curPos.x - this->mousePosWindow.x; /* X side */
	float dy = curPos.y - this->mousePosWindow.y; /* Y side */

	/* Calculate the X side length and Y side length of right triangle formed from player position to mouse position */
	float ypos = this->mousePosWindow.y - playerPos.y; /* X side */
	float xpos = this->mousePosWindow.x - playerPos.x; /* Y side */
	/* Get the magnitude of the vector formed from player position to mouse position */
	float magnitude = std::sqrt((xpos * xpos) + (ypos * ypos));

	//Debug
	//std::cout << "YPos: " << ypos << " XPos: " << xpos << " Magnitude: " << magnitude << "\n" ;
	
	/* Check to make sure magnitude is not 0 (Avoid division by zero) */
	if (magnitude > 0 || magnitude < 0)
	{ 
		/* Normalize vector from player position to mouse position */
		vertices[1].position = sf::Vector2f(xpos / magnitude, ypos / magnitude );
	}

	//Debug
	//std::cout << vertices[1].position.x << " " << vertices[1].position.y << "\n";

	/* Calculate the angle between sword and mouse position */
	float rotation = (atan2(dy, dx)) * 180 / PI;
	/* Rotate sword based on mouse position, have sword point to mouse */
	this->item.setRotation(rotation + 315);

	/* Set radius of sword rotation around player */
	float radius = 40;

	/* Set position of sword based on normalized vector from above * the radius of the cirlce and centers the revolution around player's current position */
	this->item.setPosition((vertices[1].position.x * radius) + playerPos.x, (vertices[1].position.y * radius) + playerPos.y);

}

void Sword::floatSword()
{
	/* Left and Right bounds check */
	if (this->item.getGlobalBounds().left < this->swordBounds.left) /* Left */
	{
		this->swingVelocity.x = 1.f;
	}
	else if (this->item.getGlobalBounds().left + this->item.getGlobalBounds().width > this->swordBounds.left + this->swordBounds.width) /* Right */
	{
		this->swingVelocity.x = -1.f;
	}

	if (this->item.getGlobalBounds().top < this->swordBounds.top)
	{
		this->swingVelocity.y = 1.f;
	}
	else if (this->item.getGlobalBounds().top + this->item.getGlobalBounds().height > this->swordBounds.top + this->swordBounds.height)
	{
		this->swingVelocity.y = -1.f;
	}

	/* Move */
	this->item.setPosition(this->item.getPosition().x + this->swingVelocity.x, this->item.getPosition().y + this->swingVelocity.y);
}

void Sword::resetSword()
{
	
}

void Sword::Render(sf::RenderTarget& target)
{
	if (this->isEquipped) /* Draw sword if it is equipped */
	{
		target.draw(this->item);
	}
	else/* Do NOT draw sword if not equipped */
	{

	}
}




