#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenu_keybinds.txt");
	if (!ifs.is_open())
	{
		throw "ERROR::InitKeybinds()::Game could not load main menu keybinds config file";
	}

	/*
	* -Create local vars to store file key_bind:key input
	* -Loop through file lines until eof, reading in a key_bind:key map pair
	* -Closes file stream
	*/
	std::string key_bind = "";
	std::string key = "";
	while (ifs >> key_bind >> key)
	{
		this->keyBinds[key_bind] = this->stateData->supportedKeys->at(key);
	}
	

	ifs.close();
}

void MainMenuState::initButtons()
{
	/*
	* Buttons:
	* New Game - start a new game state
	* Load Game - opens load game state
	* Library - opens a library state
	* Hero Profile - opens a hero profile state
	* Settings - opens a settings state
	* Editor - Opens a new editor state
	* Quit - Quit the game
	*/

	/* Local vars for readability */
	float pos_x(100.f), pos_y(500.f), button_width(200.f), button_height(100.f);
	unsigned int button_text_character_size(90);
	sf::Color idle_Text_Color(180, 180, 180, 240), hover_Text_Color(205, 205, 205, 240), active_Text_Color(255, 255, 255, 240),
		idle_Color(0, 0, 0, 0), hover_Color(255, 255, 255, 120), active_color(250, 250, 250, 0);
		
	/* Init the new game button and store into editorstate's button std::map */
	this->buttons["NEW_GAME"] = new gui::Button(pos_x, pos_y, button_width, button_height,
		"New Game", this->stateData->font->marketDeco, button_text_character_size,
		idle_Text_Color, hover_Text_Color, active_Text_Color,
		idle_Color, hover_Color, active_color);
	
	/* Init the Editor button and store into editorstate's button std::map */
	this->buttons["EDITOR"] = new gui::Button(pos_x, pos_y + 100, button_width, button_height,
		"Editor", this->stateData->font->marketDeco, button_text_character_size,
		idle_Text_Color, hover_Text_Color, active_Text_Color,
		idle_Color, hover_Color, active_color);
	


}

void MainMenuState::initGui()
{

	this->background.setSize(sf::Vector2f(static_cast<float>(this->stateData->window->getSize().x),
		static_cast<float>(this->stateData->window->getSize().y)));
	if (!this->backgroundImage.loadFromFile("Resources/Images/Sprites/Background/MainMenu.png"))
	{
		throw "ERROR::InitGui()::MAINMENUSTATE could not open main menu background image ";
	}

	/* Init background rectangle */
	this->background.setTexture(&this->backgroundImage);
	
	/* Title background strip */
	this->backgroundStrip.setSize(sf::Vector2f(this->stateData->window->getSize().x + (this->stateData->window->getSize().x / 2), this->stateData->window->getSize().y / 9));
	this->backgroundStrip.setFillColor(sf::Color(20, 20, 20, 100));
	this->backgroundStrip.setOrigin(this->backgroundStrip.getGlobalBounds().width / 2.f, this->backgroundStrip.getGlobalBounds().height / 2.f);
	this->backgroundStrip.setPosition(this->stateData->window->getSize().x / 2, this->stateData->window->getSize().y / 5.25f);
	

	/* Title */
	this->title.setFont(this->stateData->font->dashHorizon);
	this->title.setString("FUNKER SHNIT");
	this->title.setCharacterSize(140.f);
	this->title.setFillColor(sf::Color::White);
	this->title.setOrigin(this->title.getGlobalBounds().width / 2.f, this->title.getGlobalBounds().height / 2.f);
	this->title.setPosition(this->stateData->window->getSize().x / 2.f + 300, this->stateData->window->getSize().y / 5.f);

}



MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initKeybinds();
	this->initGui();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Update(const float& dt)
{
	this->updateMousePos();
	this->updateKeytime(dt);
	this->updateInput();
	this->updateButtons();
}

void MainMenuState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime())
	{
		this->endState();
	}

	if (this->buttons["NEW_GAME"]->isPressed())
	{
		this->stateData->states->push(new GameState(this->stateData));
	}
	if (this->buttons["EDITOR"]->isPressed())
	{
		this->stateData->states->push(new EditorState(this->stateData));
	}
	
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->Update(this->mousePosView);
	}
}


void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target) { target = this->stateData->window; }

	target->draw(this->background);
	target->draw(this->backgroundStrip);
	target->draw(this->title);
	

	this->renderButtons(*target);

	
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->Render(target);
	}
}
