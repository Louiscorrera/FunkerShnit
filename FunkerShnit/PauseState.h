#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "gui.h"

enum PauseMenuAction {CLEAR = 0, SAVE, LOAD};

class PauseState : public State
{


private:
	/**** DATA MEMBERS ****/

	/** Virtuals(From State) **/
	/* std::map<std::string, int> keyBinds */

	/* Graphics */
	sf::RectangleShape pauseMenuBackground;
	Fonts* Font;
	Colors* Color;
	
	/* Buttons */
	std::map<std::string, gui::Button*> buttons;

	/* Trackers */
	bool isPaused;
	unsigned int pauseAction;

	/**** METHODS(Private) ****/
	/** Pure Virtuals(From State) **/
	void initKeybinds() override;
	/** Non-Pure Virtuals **/
	void initGraphics();
	void initButtons();

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	PauseState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f, Fonts& fonts, Colors& color);
	~PauseState();

	/**** ACCESSORS ****/
	void togglePaused();
	const int& getPauseAction();
	const bool& getPaused() const;
	/**** METHODS ****/

	/*** Updates ***/
	/** Pure Virtuals(From State) **/
	void Update(const float& dt) override;
	void editorUpdate(const float& dt, sf::Vector2f mouse_pos_window);
	void updateButtons(sf::Vector2f mouse_pos_window);

	/*** Renders ***/
	/** Pure Virtuals(From State) **/
	void Render(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget& target);
};



#endif // !PAUSESTATE_H