#ifndef CARD_H
#define CARD_H

#include "MainMenuState.h"

struct Gfxettings 
{
	/** Window Settings **/
	sf::VideoMode videoMode;
	std::string title;
	bool fullscreen;
	int frameRateLimit;

	/** Game Dimensions **/
	float gridSizeF;

};
class Game
{

private:

	/**** DATA MEMBERS ****/

	/** State Stack **/
	std::stack<State*> states;

	/** Window **/
	sf::RenderWindow* window;
	Gfxettings gfxSettings;
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


#endif

