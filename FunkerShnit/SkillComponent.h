#pragma once

enum Skills{ATTACK = 0, DEFENSE, HEALTH, COMBATLEVEL};

class SkillComponent
{
private:
	/**** DATA MEMBERS ****/

	/* Skills */
	std::string skill;

	int level;
	int nextLevel;
	float totalExp;
	float lastLevel;
	float toNextlevel;
	
	int id;

	/**** METHODS(Private) ****/

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	SkillComponent(std::string skill_type, int starting_level = 1);
	virtual ~SkillComponent();

	/**** ACCESSORS ****/
	const std::string& getSkillType() const;
	const int getSkillId() const;
	const float getSkillLevel() const;

	/**** METHODS ****/
	std::string gainExperience(int experience_amount);
	void looseExperience(int experience_amount);
	std::string levelUp();
	/*** Updates ***/
	void updateNextLevel();

	/*** Renders ***/

};

