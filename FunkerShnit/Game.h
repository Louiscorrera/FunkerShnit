#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"



class Game
{

private:

	/**** DATA MEMBERS ****/

	/* State Data - Contains State Stack, Window, Keybinds */
	StateData* stateData;

	/* State Stack */
	std::stack<State*> states;

	/** Window **/
	sf::RenderWindow* window;

	/** Keybinds **/
	std::map<std::string, int> supportedKeys;

	/* Mouse */
	sf::Vector2i mouseDesktopPos;

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
	void initStateData();

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




#endif

