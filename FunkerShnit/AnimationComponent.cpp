#include "stdafx.h"
#include "AnimationComponent.h"


#include "Stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	//Deleting all animations in map
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key,
	float animation_timer,
	int start_frame_x, int start_framt_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_framt_y, frames_x, frames_y, width, height);
}



const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

void AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{

	//check if there is a priority animation
	if (this->priorityAnimation)
	{
		//If the priority animation is this current animation
		if (this->priorityAnimation == this->animations[key])
		{
			//Check if this animation is the last animation
			if (this->lastAnimation != this->animations[key])
			{
				//If it is the last animation, and last animation is null set the last animation to this current animation
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else //If this animation is the last animation then reset the animation
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
				//If priority animation is done, clear any priority animations
				if (this->animations[key]->play(dt)) {
					this->priorityAnimation = NULL;
				}
			}
		}
	}
	else
	{
		//If this is a priority animation, set it to the priority animation
		if (priority == true)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt);
	}
}

void AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float modifier_max, const bool priority)
{
	//check if there is a priority animation
	if (this->priorityAnimation)
	{
		//If the priority animation is this current animation
		if (this->priorityAnimation == this->animations[key])
		{
			//Check if this animation is the last animation
			if (this->lastAnimation != this->animations[key])
			{
				//If it is the last animation, and last animation is null set the last animation to this current animation
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else //If this animation is the last animation then reset the animation
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			//If the prio animation is done reset priority animation to NULL(reset)
			if (this->animations[key]->play(dt, abs(modifier / modifier_max))) {

				this->priorityAnimation = NULL;
			}

		}
	}
	else
	{
		//If this is a priority animation, set it to the priority animation
		if (priority == true)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

}
