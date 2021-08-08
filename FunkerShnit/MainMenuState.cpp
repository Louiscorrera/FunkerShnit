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
		this->keyBinds[key_bind] = this->supportedKeys->at(key);
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
	float pos_x(100.f), pos_y(100.f), button_width(150.f), button_height(60.f);
	unsigned int button_text_character_size(30);
	sf::Color idle_Text_Color(160, 160, 160, 240), hover_Text_Color(200, 200, 200, 240), active_Text_Color(200, 200, 200, 240),
		idle_Color(0, 0, 0, 0), hover_Color(45, 45, 45, 0), active_color(250, 250, 250, 0);
		
	/* Init the new game button and store into editorstate's button std::map */
	this->buttons["NEW_GAME"] = new gui::Button(pos_x, pos_y, button_width, button_height,
		"New Game", this->font->franchise, button_text_character_size,
		idle_Text_Color, hover_Text_Color, active_Text_Color,
		idle_Color, hover_Color, active_color);
	
	/* Init the Editor button and store into editorstate's button std::map */
	this->buttons["EDITOR"] = new gui::Button(pos_x, pos_y + 100, button_width, button_height,
		"Editor", this->font->franchise, button_text_character_size,
		idle_Text_Color, hover_Text_Color, active_Text_Color,
		idle_Color, hover_Color, active_color);
	


}



MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f)
	:State(window, supportedKeys, states, grid_size_f)
{
	this->initKeybinds();

	this->initButtons();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Update(const float& dt)
{
	this->updateMousePos();
	this->updateInput();
	this->updateButtons();
}

void MainMenuState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))))
	{
		this->endState();
	}

	if (this->buttons["NEW_GAME"]->isPressed())
	{
		this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states, this->grifSizeF));
	}
	if (this->buttons["EDITOR"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states, this->grifSizeF));
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
	if (!target) { target = this->window; }

	this->renderButtons(*target);
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->Render(target);
	}
}
