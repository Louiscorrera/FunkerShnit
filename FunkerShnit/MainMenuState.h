#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "EditorState.h"

class MainMenuState : public State
{
private:
	/**** DATA MEMBERS ****/
	
	/** Virtuals(From State) **/
	/* std::map<std::string, int> keyBinds */

	/** Non-Pure Virtuals **/
	/* Button */
	std::map<std::string, gui::Button*> buttons;

	/**** METHODS(Private) ****/

	/*** Inits ***/
	/** Pure Virtuals(From State) **/
	void initKeybinds() override;
	/** Non-Pure Virtuals **/
	void initButtons();
	

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f);
	virtual ~MainMenuState();

	/**** ACCESSORS ****/
	

	/**** METHODS ****/

	/*** Updates ***/
	/** Pure Virtuals(From State) **/
	void Update(const float& dt) override;
	/* Non-Pure Virtuals */
	void updateInput();
	void updateButtons();
	

	/*** Renders ***/
	/** Pure Virtuals(From State) **/
	void Render(sf::RenderTarget* target = NULL) override;
	/* Non-Pure Virtuals */
	void renderButtons(sf::RenderTarget& target);

};


#endif // !MAINMENUSTATE_H
