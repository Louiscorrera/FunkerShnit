#include "stdafx.h"
#include "Sword.h"

void Sword::initHitboxComponent() {

	this->swordHitboxComponent = new HitboxComponent(this->item, 20, 80, this->item.getGlobalBounds().width / 4, this->item.getGlobalBounds().height/2.f + 18, true);
	
}

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
	this->combat = false;
	this->isAttacking = false;
	

	this->swordAttack = SwordAttack::DEFAULT;
	this->swingVelocity.x = 5.f;
	this->swingVelocity.y = 5.f;

	this->attackTimer = 0.f;
	this->attackTimerReset = 50.f;
	this->attackTime = 0.f;

	this->mousePosWindow.x = 0;
	this->mousePosWindow.y = 0;
}

Sword::Sword(std::string item_name, unsigned int item_level, unsigned int item_value, unsigned int item_weight, 
	bool item_wieldable, bool item_consumable, 
	sf::Texture& item_texture)
	:Weapon(item_name, item_level, item_value, item_weight, item_wieldable, item_consumable, item_texture)
{
	
	this->initTexture();
	this->initVars();
	this->initHitboxComponent();

	/* Set Sword Idle Range  */
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
	return this->combat;
}

const sf::FloatRect Sword::getSwordHitBox() const
{
	if (this->swordHitboxComponent)
	{
		return sf::FloatRect(this->swordHitboxComponent->getHitboxGlobalBounds());
	}
	std::cout << "ERROR::GetSwordHitBox()::SWORD returned a 0, 0, 0, 0 float rect because no hitbox component exists\n";
	return sf::FloatRect(0, 0, 0, 0);
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
	this->combat = !this->combat;
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






void Sword::updateAttackTimer(const float& dt)
{
	if (this->attackTimer < this->attackTimerReset)
	{
		this->attackTimer += 1000.f * dt;
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
		
		if (this->combat) //If the sword is attacking check which attack state the sword is in and animate accordingly
		{
			if (this->isAttacking)
			{
				this->attack();
			}
			else
			{
				this->rotateSword(playerBounds);
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
	this->swordHitboxComponent->setRotation(rotation + 95);

	/* Set radius of sword rotation around player */
	float radius = 40;

	/* Set position of sword based on normalized vector from above * the radius of the cirlce and centers the revolution around player's current position */
	this->item.setPosition((vertices[1].position.x * radius) + playerPos.x, (vertices[1].position.y * radius) + playerPos.y);
	this->updateHitbox();

}

void Sword::floatSword()
{
	/* Left and Right bounds check */
	if (this->item.getGlobalBounds().left < this->swordBounds.left) /* Left */
	{
		this->swingVelocity.x = 0.8f;
	}
	else if (this->item.getGlobalBounds().left + this->item.getGlobalBounds().width > this->swordBounds.left + this->swordBounds.width) /* Right */
	{
		this->swingVelocity.x = -0.8f;
	}

	if (this->item.getGlobalBounds().top < this->swordBounds.top)
	{
		this->swingVelocity.y = 0.8f;
	}
	else if (this->item.getGlobalBounds().top + this->item.getGlobalBounds().height > this->swordBounds.top + this->swordBounds.height)
	{
		this->swingVelocity.y = -0.8f;
	}

	/* Move */
	this->item.setPosition(this->item.getPosition().x + this->swingVelocity.x, this->item.getPosition().y + this->swingVelocity.y);
	this->updateHitbox();
}

void Sword::updateHitbox(float rotation)
{
	this->swordHitboxComponent->setPosition(sf::Vector2f(this->item.getPosition().x, this->item.getPosition().y));
	
	if (rotation >= 0)
	{
		this->swordHitboxComponent->setRotation(rotation);
	}
}

void Sword::attack()
{
	this->attackY = this->mousePosWindow.y - this->item.getPosition().y;
	this->attackX = this->mousePosWindow.x - this->item.getPosition().x;

	float mag = std::sqrt(pow(this->attackX, 2) + pow(this->attackY, 2));
	sf::Vector2f normal_vec(this->attackX / mag, this->attackY / mag);

	if (this->isAttacking && this->combat)
	{
		this->item.setPosition(this->item.getPosition().x + normal_vec.x * 5, this->item.getPosition().y + normal_vec.y * 5);
		this->updateHitbox();
		if (this->attackTime > 15)
		{
			this->isAttacking = false;
			this->attackTime = 0.f;
		}
		else
		{
			this->attackTime++;
		}
	}


}



void Sword::resetSword()
{
	
}


void Sword::Render(sf::RenderTarget& target)
{
	if (this->isEquipped) /* Draw sword if it is equipped */
	{
		target.draw(this->item);
		this->swordHitboxComponent->render(target);
	}
	else/* Do NOT draw sword if not equipped */
	{

	}
}




