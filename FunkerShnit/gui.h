#ifndef GUI_H
#define GUI_H

/*#include "State.h"
#include "TileMap.h"*/






namespace gui {

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


	enum button_States{BUTTON_IDLE = 0, BUTTON_HOVER, BUTTON_ACTIVE};

	class Button
	{
	/**** DATA MEMBERS ****/

		/* Button State*/
		unsigned int buttonState;

		/* Shape */
		sf::RectangleShape buttonShape;

		/* Text */
		sf::Font* buttonFont;
		sf::Text buttonText;
		std::string buttonName;

		/** Color **/
		/* Button */
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;
		/* Text */
		sf::Color idleTextColor;
		sf::Color hoverTextColor;
		sf::Color activeTextColor;


	/**** METHODS(Private) ****/

	/*** Inits ***/
		void initVars();

	protected:

	public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
		Button(float Pos_x, float Pos_y, float button_width, float button_height,
			std::string button_text, sf::Font& buttonTextFont, unsigned int character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
		~Button();

	/**** ACCESSORS ****/
		const bool& isPressed();

	/**** METHODS ****/

	/*** Updates ***/
		void Update(const sf::Vector2f mousePos);

	/*** Renders ***/
		void Render(sf::RenderTarget& target);
	};	


	class EditorTextureSelector
	{
	private:
		/**** DATA MEMBERS ****/

		/* Global Game data(not actually a global var) */
		float gridsizeF;

		/* Selector Interface */
		sf::RectangleShape selectorBox; //Box to render the available textures
		sf::RectangleShape textureSelectorGuide; //Rect to help user see what texture they are selecting
		sf::Sprite textureHolder; //Sprite to hold the textures available to user (to display in selectorBox)
		sf::IntRect textureSelector; //rectangle to allow user see what select texture they are going to select

		/* Window Control */
		bool isHidden;
		gui::Button* hideButton;
		float keyTime;
		float keyTimeMax;

		/* Mouse Interface */
		sf::Vector2u mousePosGridSelector;
		bool isActive; //To determine if mouse is within texture selector box interface

		/* Fonts & Colors(From STATE) */
		Fonts* font;
		Colors* color;

		/**** METHODS(Private) ****/
		/*** Inits ***/
		void initButtons();
	

	protected:

	public:
		/**** CONSTRUCTOR | DESTRUCTOR ****/
		EditorTextureSelector(float pos_x, float pos_y, float width, float height, float grid_size_f, sf::Texture* tile_sheet_texture, gui::Fonts* fonts, gui::Colors* colors);
		~EditorTextureSelector();

		/**** ACCESSORS ****/
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool& getHidden() const;
		const bool& getKeyTimer();

		/**** METHODS ****/

		/*** Updates ***/
		void Update(const sf::Vector2i& mouse_pos_window, const float& dt);
		void updateButtons(sf::Vector2f mouse_pos_grid);
		void updateKeyTime(const float& dt);

		/*** Renders ***/
		void Render(sf::RenderTarget& target);
		void renderButtons();
	};



	class TextInputBox
	{
	private:
		/**** DATA MEMBERS ****/
		
		/* Input Box */
		sf::RectangleShape textBox;
		float posX;
		float posY;
		float textBoxWidth;
		float textBoxHeight;

		sf::Color textBoxColor;
		sf::Font* textFont;
		sf::Text textBoxText;
		

		//std::vector<char> workingText;

		sf::RenderWindow* window;
		

		/**** METHODS(Private) ****/
		void initVars();
		void initTextBox();

	protected:

	public:

		std::string text;

		/**** CONSTRUCTOR | DESTRUCTOR ****/
		TextInputBox(float pos_x, float pos_y, float text_box_width, float text_box_height, sf::Color text_box_color, sf::Font& font, sf::RenderWindow* window);
		~TextInputBox();

		/**** ACCESSORS ****/

		/**** METHODS ****/

		/*** Updates ***/
		void Update(sf::Event* sfmlevent);

		/*** Renders ***/
		void Render(sf::RenderTarget& targe);
	};





	enum PauseMenuAction { NONE = 0, SAVE, LOAD, CLEAR };
	class PauseMenu
	{

	private:
		/**** DATA MEMBERS ****/

		/* Background */
		sf::RectangleShape background;

		/* State Data */
		sf::RenderWindow* window;

		/* Buttons */
		std::map<std::string, gui::Button*> buttons;

		/* Trackers */
		bool isPaused;
		unsigned int pauseAction;

		/* Key Timer */
		float keyTime;
		float maxKeyTime;

		/* Mouse */
		sf::Vector2f mousePosWindow;

		gui::Fonts* font;
		gui::Colors* color;


		/**** METHODS(Private) ****/
		void initVars();
		void initGraphics();
		void initButtons();

	protected:

	public:
		/**** CONSTRUCTOR | DESTRUCTOR ****/
		PauseMenu(sf::RenderWindow* state_render_window, gui::Fonts* state_fonts, gui::Colors* state_colors);
		~PauseMenu();

		/**** ACCESSORS ****/
		const bool& getPaused() const;
		const bool& getKeyTime();
		const unsigned int& getPauseAction();

		/**** Mutators ****/
		void togglePaused();

		/**** METHODS ****/

		/*** Updates ***/
		void Update(const float& dt, sf::Vector2f mouse_pos_window);
		void updateButtons(const float& dt);
		void updateKeyTime(const float& dt);

		/*** Renders ***/
		void Render(sf::RenderTarget* target = NULL);
		void renderButtons(sf::RenderTarget& target);

	};

}

#endif