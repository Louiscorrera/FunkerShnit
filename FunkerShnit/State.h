#ifndef STATE_H
#define STATE_H


#include "TileMap.h"
#include "gui.h"

class State;

class GfxSettings
{
public:
	GfxSettings() { this->defaultSettings(); }
	~GfxSettings() {  }

	void defaultSettings() {
		this->title = "Default";
		this->resolution = sf::VideoMode::getDesktopMode();
		this->fullscreen = false;
		this->verticalSyncEnabled = false;
		this->frameRateLimit = 120;
		this->gridSizeF = 50;
	}

	void loadGfxFromFile(std::string GfxFileName);
	void saveGfxToFile(std::string GfxFileName);

	/** Window Settings **/
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSyncEnabled;
	unsigned int frameRateLimit;
	/** Game Dimensions **/
	float gridSizeF;
};

class StateData
{
public:
	StateData();
	~StateData() {
		delete this->gfxSettings;
		delete this->color;
		delete this->font;
	}

	/* Data Members */
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;

	/* Graphics */
	GfxSettings* gfxSettings;

	/* Colors __Public so all states have access to these pre defined colors */
	gui::Colors* color;
	/* Fonts __Public so all states have access to these pre defined colors */
	gui::Fonts* font;

	/* Methods */
	void initGridSize() { this->gfxSettings->gridSizeF = 50; }
	void initFontsColors() { this->font = new gui::Fonts(); this->color = new gui::Colors(); }
};


class State
{
private:
	/**** DATA MEMBERS(Private) ****/

	/** Game State **/
	bool quit;
	 

	/**** METHODS(Private) ****/
	/*** Inits ***/
	/** Pure Virtuals **/
	virtual void initKeybinds() = 0;

protected:

	/**** DATA MEMBERS(Protected) ****/

	StateData* stateData; //*** Definition/Declaration is Inside gui.h!!!! ***//

	/** Keybinds **/
	std::map<std::string, int> keyBinds;

	/* Pause Menu */
	gui::PauseMenu* pauseMenu;

	/* Keys & Time */
	float keyTime;
	float keyTimeMax;


	/** Mouse Positions **/
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	
public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	State(StateData* state_data);
	virtual ~State();

	/**** ACCESSORS ****/
	const bool& getQuit() const;
	const bool& getKeyTime();

	/**** METHODS ****/

	/*** Updates ***/
	/** Pure Virtuals **/
	virtual void Update(const float& dt) = 0;
	/* Non-Pure Virtuals */
	virtual void updateMousePos(sf::View* view = NULL); //Updates view & window mouse positions
	virtual void updateKeytime(const float& d);
	void endState();

	/*** Renders ***/
	/** Pure Virtuals **/
	virtual void Render(sf::RenderTarget* target = NULL) = 0;
	/* Non-Pure Virtuals */


};






#endif

