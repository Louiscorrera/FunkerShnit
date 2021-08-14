#ifndef STATE_H
#define STATE_H



struct Colors
{
	/* Colors */
	sf::Color pukeGreen;
	sf::Color darkRed;
	sf::Color lightPurple1;
	sf::Color darkPurple1;
	sf::Color darkPurple2;
	sf::Color lightGreen;
	sf::Color teal;
	sf::Color lightGrey;
	sf::Color lighterGrey;

	Colors();

	void initColors();
};

struct Fonts
{
	sf::Font corleone;
	sf::Font dashHorizon;
	sf::Font franchise;
	sf::Font marketDeco;
	sf::Font amazDoomRight;

	Fonts();

	void initFonts();
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
	/* Non-Pure Virtuals*/
	void initColors();
	void initFonts();

protected:

	/**** DATA MEMBERS(Protected) ****/

	/** State Stack **/
	std::stack<State*>* states;

	/** Window **/
	sf::RenderWindow* window;

	/** Game Dimension **/
	float grifSizeF;

	/** Keybinds **/
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;

	/* Keys & Time */
	float keyTime;
	float keyTimeMax;


	/** Mouse Positions **/
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	
public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f);
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


	/* Colors __Public so all states have access to these pre defined colors */
	Colors* color;
	/* Fonts __Public so all states have access to these pre defined colors */\
	Fonts* font;

};






#endif

