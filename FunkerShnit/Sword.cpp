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
	this->swordBounds = sf::FloatRect(this->entityBounds.left, this->entityBounds.top, this->entityBounds.width * 2, this->entityBounds.height * 2);
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
			this->item.setPosition(this->entityBounds.left - 2, this->entityBounds.top - 2);
			this->rotateSword(playerBounds);
		}
	}
	else {} /* Sword is not equipped */
}\


void Sword::rotateSword(sf::FloatRect playerBounds)
{
	sf::Vector2f curPos = this->item.getPosition();
	sf::Vector2f playerPos = sf::Vector2f(playerBounds.width/2.f, playerBounds.height/2.f);
	
	sf::Vertex vertices[2];
	vertices[0].position = sf::Vector2f(playerPos.x, playerPos.y);
	vertices[1].position = sf::Vector2f(this->mousePosWindow.x, this->mousePosWindow.y);

	float radius = 40;

	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	const float PI = 3.14159265;

	float dx = curPos.x - this->mousePosWindow.x;
	float dy = curPos.y - this->mousePosWindow.y;

	float ypos = playerPos.y - this->mousePosWindow.y;
	float xpos = -(playerPos.x - this->mousePosWindow.x); 

	float magnitude = std::sqrt(pow(xpos, 2) + pow(ypos, 2));

	//std::cout << "YPos: " << ypos << " XPos: " << xpos << " Magnitude: " << magnitude << "\n" ;

	if (magnitude > 0)
	{
		vertices[1].position = sf::Vector2f(this->mousePosWindow.x / magnitude, this->mousePosWindow.y / magnitude);
	}

	std::cout << vertices[1].position.x << " " << vertices[1].position.y << "\n";

	float rotation = (atan2(dy, dx)) * 180 / PI;
	//float angle = (atan2(this->mousePosWindow.y - playerPos.y, this->mousePosWindow.x - playerPos.x)) * 180 / PI;

	this->item.setRotation(rotation + 315);

	float originX = playerBounds.width / 2.f;
	float originY = playerBounds.height / 2.f;

	//this->item.move(playerPos.x + radius*std::cos(angle), playerPos.y + radius*std::sin(angle)); 
	this->item.move(originX + vertices[1].position.x * radius, originY + vertices[1].position.y * radius);

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




