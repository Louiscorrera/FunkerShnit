#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState : public State
{
private:
	/**** DATA MEMBERS ****/
	
	/** Virtuals(From State) **/
	/* std::map<std::string, int> keyBinds */

	/** Non-Pure Virtuals **/
	/* Button */
	std::map<std::string, gui::Button*> buttons;

	/* Background */
	sf::Texture backgroundImage;
	sf::RectangleShape background;

	sf::RectangleShape backgroundStrip;

	sf::Text title;

	/**** METHODS(Private) ****/

	/*** Inits ***/
	/** Pure Virtuals(From State) **/
	void initKeybinds() override;
	/** Non-Pure Virtuals **/
	void initButtons();
	void initGui();
	

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	MainMenuState(StateData* state_data);
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
