#include "stdafx.h"
#include "gui.h"





						  /****/
				/************************/
				/**** Namespace gui ****/
				/***********************/
						  /****/




/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/


		/*******************************/
		/******** Colors & Fonts *******/
		/*******************************/



/* Colors */
/* WARNING: Can be accessed anywhere in a state and manipulated */
gui::Colors::Colors()
{
	this->initColors();
}


void gui::Colors::initColors()
{
	this->pukeGreen = sf::Color(204, 204, 0, 255);
	this->darkRed = sf::Color(153, 0, 0, 255);
	this->lightPurple1 = sf::Color(178, 102, 205, 255);
	this->darkPurple1 = sf::Color(102, 0, 204, 255);
	this->darkPurple2 = sf::Color(51, 0, 102, 255);
	this->lightGreen = sf::Color(51, 255, 51, 255);
	this->teal = sf::Color(0, 204, 204, 255);
	this->lightGrey = sf::Color(192, 192, 192, 255);
	this->lighterGrey = sf::Color(224, 224, 224, 255);
}



/* Fonts */
gui::Fonts::Fonts()
{
	this->initFonts();
}

void gui::Fonts::initFonts()
{
	if (!this->corleone.loadFromFile("Resources/Fonts/Corleone.ttf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
	if (!this->dashHorizon.loadFromFile("Resources/Fonts/Dash-Horizon-Demo.otf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
	if (!this->franchise.loadFromFile("Resources/Fonts/Franchise.ttf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
	if (!this->marketDeco.loadFromFile("Resources/Fonts/Market_Deco.ttf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
	if (!this->amazDoomRight.loadFromFile("Resources/Fonts/AmazDoomRight.ttf"))
	{
		throw "ERROR::InitFonts()::FONTS::STATE could not load one or more fonts from file";
	}
}

/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/


		/*******************************/
		/*********** BUTTON ***********/
		/*******************************/
void gui::Button::initVars()
{
	this->buttonState = BUTTON_IDLE;
}

gui::Button::Button(float Pos_x, float Pos_y, float button_width, float button_height,
	std::string button_name, sf::Font& buttonTextFont, unsigned int character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
	: buttonFont(&buttonTextFont), buttonName(button_name), 
	idleTextColor(text_idle_color), hoverTextColor(text_active_color), activeTextColor(text_active_color),
	idleColor(idle_color), hoverColor(hover_color), activeColor(active_color)
{
	this->initVars();

	/* Set up button shape */
	this->buttonShape.setPosition(sf::Vector2f(Pos_x, Pos_y)); //Button shape positions
	this->buttonShape.setSize(sf::Vector2f(button_width, button_height)); //Button shape size
	this->buttonShape.setFillColor(this->idleColor); //Button shape default color (idle)


	/* Set up button's font and text */
	this->buttonText.setFont(*this->buttonFont); //Button text font
	this->buttonText.setString(buttonName); //Button name
	this->buttonText.setCharacterSize(character_size); //Button text character size
	this->buttonText.setFillColor(this->idleTextColor); //Button text default color (idle)
	this->buttonText.setPosition(sf::Vector2f(
		this->buttonShape.getPosition().x + this->buttonShape.getGlobalBounds().width / 2.f - this->buttonText.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + this->buttonShape.getGlobalBounds().height / 2.f - this->buttonText.getGlobalBounds().height / 2.f
	)); //Button text position (middle of button shape)

	
}

gui::Button::~Button()
{
	
}

const bool& gui::Button::isPressed()
{
	/* Check if buttonState has been set to active, meaning the button has been "pressed" */
	if (this->buttonState == BUTTON_ACTIVE)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void gui::Button::Update(const sf::Vector2f mousePos)
{
	/* if mouse is not withing button shape */
	this->buttonState = BUTTON_IDLE;

	/* If mouse is within button shape */
	if (this->buttonShape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BUTTON_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BUTTON_ACTIVE;
		}
	}

	/* Switches the buttons color based on the state the button is in (Idle, hovered, or active)*/
	switch (buttonState)
	{
	case BUTTON_IDLE:
		this->buttonShape.setFillColor(this->idleColor);
		this->buttonText.setFillColor(this->idleTextColor);
		break;
	case BUTTON_HOVER:
		this->buttonShape.setFillColor(this->hoverColor);
		this->buttonText.setFillColor(this->hoverTextColor);
		break;
	case BUTTON_ACTIVE:
		this->buttonShape.setFillColor(this->activeColor);
		this->buttonText.setFillColor(this->activeTextColor);
		break;
	default: /* Default values, should not ever be the case */
		this->buttonShape.setFillColor(sf::Color::Black);
		this->buttonText.setFillColor(sf::Color::White);
		break;
	}

}

void gui::Button::Render(sf::RenderTarget& target)
{
	target.draw(this->buttonShape);
	target.draw(this->buttonText);
}



/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/



		/*******************************/
		/****** TEXTURE SELECTOR *******/
		/*******************************/

void gui::EditorTextureSelector::initButtons()
{
	

	/* Init the Hide and reveal texture selector interface button */
	this->hideButton = new Button(this->selectorBox.getPosition().x - this->selectorBox.getPosition().x, this->selectorBox.getPosition().y - this->selectorBox.getPosition().y, 100.f, 50.f,
		"Hide/Show", this->font->amazDoomRight, 25,
		sf::Color::Black, this->color->lighterGrey, sf::Color::White,
		this->color->lightPurple1, this->color->darkPurple1, this->color->darkPurple2);
}


gui::EditorTextureSelector::EditorTextureSelector(float pos_x, float pos_y, float width, float height, float grid_size_f, sf::Texture* tile_sheet_texture, Fonts* fonts, Colors* colors)
	: gridsizeF(grid_size_f), isActive(true), isHidden(false), font(fonts), color(colors)
{
	/* Init selector box */
	this->selectorBox.setSize(sf::Vector2f(width, height));
	this->selectorBox.setPosition(sf::Vector2f(pos_x, pos_y));
	this->color->lightGrey.a = 50; //Make more transparent
	this->selectorBox.setFillColor(this->color->lightGrey);
	this->selectorBox.setOutlineThickness(1.f);
	this->selectorBox.setOutlineColor(sf::Color::White);

	/* Init buttons __Here Because button init uses selectorBox's positions for it's own position */
	this->initButtons();

	/* Init the sprite that will hold the texture sheet inside the selector box */ //TODO: Figure out a way to have multiple textures loaded in
	this->textureHolder.setTexture(*tile_sheet_texture);
	this->textureHolder.setPosition(pos_x, pos_y);

	/* Checks to make sure the sprite holding the texture sheet is within the texture selector's box */
	if (this->textureHolder.getGlobalBounds().width > this->selectorBox.getGlobalBounds().width)
	{
		this->textureHolder.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->selectorBox.getGlobalBounds().width), static_cast<int>(this->textureHolder.getGlobalBounds().height)));
	}
	if (this->textureHolder.getGlobalBounds().height > this->selectorBox.getGlobalBounds().height)
	{
		this->textureHolder.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->textureHolder.getGlobalBounds().width), static_cast<int>(this->selectorBox.getGlobalBounds().height)));
	}

	/* Init the texture selector guide's fill color, and outline thickness & outline color */
	this->textureSelectorGuide.setSize(sf::Vector2f(this->gridsizeF, this->gridsizeF));
	this->textureSelectorGuide.setFillColor(this->color->lightGrey);
	this->textureSelectorGuide.setOutlineThickness(2.f);
	this->textureSelectorGuide.setOutlineColor(sf::Color::Red);

	/* Inits the height and width of the intRect that will choose the texture to draw with */
	this->textureSelector.width = static_cast<int>(this->gridsizeF);
	this->textureSelector.height = static_cast<int>(this->gridsizeF);

	/* Init timer */
	this->keyTime = 0.f;
	this->keyTimeMax = 15.f;



	this->color->lightGrey.a = 255; //Return OG transparency
}

gui::EditorTextureSelector::~EditorTextureSelector()
{
	delete this->hideButton;
}

const sf::IntRect& gui::EditorTextureSelector::getTextureRect() const
{
	return this->textureSelector;
}

const bool& gui::EditorTextureSelector::getHidden() const
{
	return this->isHidden;
}

const bool& gui::EditorTextureSelector::getKeyTimer()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	else { return false; }
}

const bool& gui::EditorTextureSelector::getActive() const
{
	return this->isActive;
}



void gui::EditorTextureSelector::Update(const sf::Vector2i& mouse_pos_window, const float& dt)
{


	this->updateKeyTime(dt);;

	if (this->isHidden == true)
	{
		if (this->hideButton->isPressed() && this->getKeyTimer())
		{
			this->isHidden = false;
		}
		else
		{

		}
	}
	else
	{
		if (this->hideButton->isPressed() && this->getKeyTimer())
		{
			this->isHidden = true;
		}
		else
		{
			/* Check if mouse has gone inside selector box */
			if (this->selectorBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window)))
			{
				this->isActive = true;
			}
			else
			{
				this->isActive = false;
			}

			/* If mouse is inside the selector box activate the textureSelectorGuide and update with mouseGridPos coords */
			if (this->isActive)
			{

				/* Convert mouseGridPos (sf::Vector2f) to an sf::Vector2i type */
				this->mousePosGridSelector.x = static_cast<unsigned int>((mouse_pos_window.x - static_cast<int>(this->selectorBox.getPosition().x)) / static_cast<unsigned int>(this->gridsizeF));
				this->mousePosGridSelector.y = static_cast<unsigned int>((mouse_pos_window.y - static_cast<int>(this->selectorBox.getPosition().y)) / static_cast<unsigned int>(this->gridsizeF));

				/* Set textureSelectorGuide box to the current mouse grid position based off the selector box interface */
				
				this->textureSelectorGuide.setPosition(
					this->selectorBox.getPosition().x + this->mousePosGridSelector.x * this->gridsizeF,
					this->selectorBox.getPosition().y + this->mousePosGridSelector.y * this->gridsizeF
				);

				

				/* Checks if the texture selector guide is within the texture holder sprite
				* -True: sets texture selector guide to green to indicate to user their selection is a VALID TEXTURE to select
				* -False: sets texture selector guide to red to indicate to user their selection is an INVALID TEXTURE to select
				*/
				if (this->textureSelectorGuide.getPosition().y <= this->textureHolder.getGlobalBounds().height)
				{
					this->textureSelectorGuide.setOutlineColor(this->color->lightGreen);
				}
				else
				{
					this->textureSelectorGuide.setOutlineColor(this->color->darkRed);

				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTimer())
				{
					/* Update the texture selector rectangle */
					this->textureSelector.left = static_cast<int>(this->textureSelectorGuide.getPosition().x - this->selectorBox.getPosition().x);
					this->textureSelector.top = static_cast<int>(this->textureSelectorGuide.getPosition().y - this->selectorBox.getPosition().y);
				}

				
			}
			else 
			{

			}
		}


	}

	

	this->updateButtons(static_cast<sf::Vector2f>(mouse_pos_window));

}

void gui::EditorTextureSelector::updateButtons(sf::Vector2f mouse_pos_grid)
{
	this->hideButton->Update(mouse_pos_grid);
}

void gui::EditorTextureSelector::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 100.f * dt;
	}
	
}


void gui::EditorTextureSelector::Render(sf::RenderTarget& target)
{
		this->hideButton->Render(target);

		if (this->getHidden() == false)
		{
			target.draw(this->selectorBox); //Draw the sprite before the texture selector's box 
			target.draw(this->textureHolder); //Draw the texture selector's box
			
				/* If mouse is inside textor selector draw the selector rectangle guide */
			if (this->isActive) { target.draw(this->textureSelectorGuide); }
		}
	
}

void gui::EditorTextureSelector::renderButtons()
{
}




/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/


		/*******************************/
		/******** TextInput Box ********/
		/*******************************/



void gui::TextInputBox::initVars()
{
	this->textBoxText.setFont(*this->textFont);
	text = " ";
	this->textBoxText.setString(text);
	this->textBoxText.setCharacterSize(30);
	this->textBoxText.setFillColor(sf::Color::White);
	this->textBoxText.setPosition(sf::Vector2f(this->posX, this->posY));
}

void gui::TextInputBox::initTextBox()
{
	this->textBox.setPosition(sf::Vector2f(this->posX, this->posY));
	this->textBox.setSize(sf::Vector2f(this->textBoxWidth, this->textBoxHeight));
	this->textBox.setFillColor(sf::Color::Black);
}

gui::TextInputBox::TextInputBox(float pos_x, float pos_y, float text_box_width, float text_box_height, sf::Color text_box_color, sf::Font& font, sf::RenderWindow* window)
	:posX(pos_x), posY(pos_y), textBoxWidth(text_box_width), textBoxHeight(text_box_height), textBoxColor(text_box_color), textFont(&font)
{
	this->initVars();
	this->initTextBox();

	this->window = window;

}

gui::TextInputBox::~TextInputBox()
{
}

void gui::TextInputBox::Update(sf::Event* sfmlevent)
{
	
		/*if (sf::Event::TextEntered)
		{
			if (sfmlevent->text.unicode < 128)
			{
				this->text += static_cast<char>(sfmlevent->text.unicode);
				this->textBoxText.setString(this->text);
			}

		}
			
			
		if (sf::Event::KeyPressed)
		{
			if (sfmlevent->key.code == sf::Keyboard::BackSpace)
			{
				//this->workingText.pop_back();
				this->text.pop_back();
				this->textBoxText.setString(this->text);
			}
		}*/

		
	
}

void gui::TextInputBox::Render(sf::RenderTarget& target)
{
	target.draw(this->textBox);
	target.draw(this->textBoxText);
}









/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/
/*=========================================================================================================================================================================*/


		/*******************************/
		/********* Pause Menu  *********/
		/*******************************/




void gui::PauseMenu::initVars()
{
	this->keyTime = 0.f;
	this->maxKeyTime = 20.f;
}

void gui::PauseMenu::initGraphics()
{
	this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->color->lighterGrey.a = 165;
	this->background.setFillColor(this->color->lighterGrey);
	this->color->lighterGrey.a = 255;
	this->background.setPosition(sf::Vector2f(this->window->getPosition()));
}

void gui::PauseMenu::initButtons()
{
	float pos_x(100.f), pos_y(500.f), button_width(150.f), button_height(60.f);
	unsigned int button_text_character_size(30);
	sf::Color idle_Text_Color(160, 160, 160, 240), hover_Text_Color(200, 200, 200, 240), active_Text_Color(200, 200, 200, 240),
		idle_Color(0, 0, 0, 0), hover_Color(45, 45, 45, 0), active_color(250, 250, 250, 0);


	/* Change colors to have 0 alpha level */


	this->buttons["SAVE"] = new gui::Button(pos_x, pos_y, button_width, button_height,
		"Save", this->font->dashHorizon, button_text_character_size,
		idle_Text_Color, hover_Text_Color, active_Text_Color,
		idle_Color, hover_Color, active_color);

	this->buttons["LOAD"] = new gui::Button(pos_x, pos_y - 100, button_width, button_height,
		"Load", this->font->dashHorizon, button_text_character_size,
		idle_Text_Color, hover_Text_Color, active_Text_Color,
		idle_Color, hover_Color, active_color);

	this->buttons["CLEAR"] = new gui::Button(pos_x, pos_y + 100, button_width, button_height,
		"Clear", this->font->dashHorizon, button_text_character_size,
		idle_Text_Color, hover_Text_Color, active_Text_Color,
		idle_Color, hover_Color, active_color);
}

gui::PauseMenu::PauseMenu(sf::RenderWindow* state_render_window, gui::Fonts* state_fonts, gui::Colors* state_colors)
	:window(state_render_window), font(state_fonts), color(state_colors)
{
	
	this->initVars();
	this->initGraphics();
	this->initButtons();
}

gui::PauseMenu::~PauseMenu()
{
}

const bool& gui::PauseMenu::getPaused() const
{
	return this->isPaused;
}

const bool& gui::PauseMenu::getKeyTime()
{
	if (this->keyTime >= this->maxKeyTime) { this->keyTime = 0.f; return true; }
	else { return false; }
}

const unsigned int& gui::PauseMenu::getPauseAction()
{
	return this->pauseAction;
}




void gui::PauseMenu::togglePaused()
{
	this->isPaused = !this->isPaused;
}



void gui::PauseMenu::Update(const float& dt, sf::Vector2f mouse_pos_window)
{
	/* Update key time */
	this->updateKeyTime(dt);

	/* Reset pause action */
	this->pauseAction = -1;

	/* Update internal cursor tracker */
	this->mousePosWindow = mouse_pos_window;

	/* Update buttons */
	this->updateButtons(dt);
}

void gui::PauseMenu::updateButtons(const float& dt)
{

	/* Update buttons */
	for (auto& it : this->buttons)
	{
		it.second->Update(this->mousePosWindow);
	}

	/* Check if buttons have been pressed */
	if (this->buttons["SAVE"]->isPressed())
	{
		this->pauseAction = PauseMenuAction::SAVE;
		//this->tileMap->saveTileMap("Test.txt");
	}
	if (this->buttons["LOAD"]->isPressed())
	{
		this->pauseAction = PauseMenuAction::LOAD;
		//this->tileMap->loadTileMap("Test.txt");
	}
	if (this->buttons["CLEAR"]->isPressed())
	{
		this->pauseAction = PauseMenuAction::CLEAR;

	}
}

void gui::PauseMenu::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->maxKeyTime) { this->keyTime += 100 * dt; }
	else {}
}



void gui::PauseMenu::Render(sf::RenderTarget* target)
{
	if (!target) { target = this->window; }

	target->draw(this->background);
	this->renderButtons(*target);
}

void gui::PauseMenu::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}
