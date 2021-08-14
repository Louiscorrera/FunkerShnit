#ifndef CARD_H
#define CARD_H

#include "MainMenuState.h"

class GfxSettings
{
public:
	GfxSettings() { this->loadGfxFromFile("Settings File name"); }
	~GfxSettings() { this->saveGfxToFile("Settings file name"); }

	void loadGfxFromFile(std::string GfxFileName);
	void saveGfxToFile(std::string GfxFileName);

	/** Window Settings **/
	sf::VideoMode screenModes;
	std::string title;
	sf::VideoMode videoMode;
	bool fullscreen;
	bool verticalSyncEnabled;
	unsigned int frameRateLimit;
	/** Game Dimensions **/
	float gridSizeF;
};

class StateData
{
public:
	StateData(){}
	~StateData() { delete this->gfxSettings; }

	/* Data Members */
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	float grid_size_f;

	/* Graphics */
	GfxSettings* gfxSettings;
};

class Game
{

private:

	/**** DATA MEMBERS ****/

	/** State Stack **/
	std::stack<State*> states;
	StateData stateData;

	/** Window **/
	sf::RenderWindow* window;
	GfxSettings gfxSettings;

	/* Mouse */
	sf::Vector2i mouseDesktopPos;

	/** Keybinds **/
	std::map<std::string, int> supportedKeys;

	/** Events **/
	sf::Event ev;

	/** Game Time **/
	sf::Clock gameClock;
	float dt;


	/**** METHODS(Private) ****/

	/*** Inits ***/
	void initVars();
	void initWindow();
	void initKeys();
	void initStateStack();

public:

	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Game();
	~Game();

	/**** Run ****/
	const bool& run();

	/**** ACCESSORS ****/

	/*** Game States ***/
	const bool& isRunning();


	/**** METHODS ****/

	/*** Updates ***/
	void Update();
	void updateTime();
	void updateSFMLEvents(); //Poll Events
	void updateMousePos();

	/*** Renders ***/
	void Render();



};


;


#endif

