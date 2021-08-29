#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent(std::string skill_type, int starting_level)
	:skill(skill_type), level(starting_level)
{
	this->id = (rand() % 50) + 1;
	this->toNextlevel = 150.f;
	this->lastLevel = this->toNextlevel;
	this->nextLevel = this->level + 1;
	this->totalExp = 0.f;
}

SkillComponent::~SkillComponent()
{
}

const std::string& SkillComponent::getSkillType() const
{
	return this->skill;
}

const int SkillComponent::getSkillId() const
{
	return this->id;
}

const float SkillComponent::getSkillLevel() const
{
	return this->level;
}

std::string SkillComponent::gainExperience(int experience_amount)
{
	std::stringstream ss;

	ss << experience_amount << " Exp";

	this->toNextlevel -= experience_amount;
	this->totalExp += experience_amount;

	if (this->toNextlevel <= 0)
	{
		return this->levelUp();
	}

	return ss.str();
}

void SkillComponent::looseExperience(int experience_amount)
{
}

std::string SkillComponent::levelUp()
{
	this->level++;
	this->nextLevel++;

	std::stringstream ss;

	ss << "Congrats you have reached level " << this->level << " " << this->skill  << "!!!\n" 
		<< "Exp to next level: " << this->toNextlevel <<"\n";
	return ss.str();
}

void SkillComponent::updateNextLevel()
{
	this->toNextlevel = this->lastLevel * 1.15;
	this->lastLevel = this->toNextlevel;
}
