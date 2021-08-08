#include "stdafx.h"
#include "PauseState.h"

void PauseState::initKeybinds()
{
	/* Opens an in file stream to read in supported keys for game */
	std::ifstream ifs("Config/pausestate_keybinds.txt");
	if (!ifs.is_open())
	{
		throw "ERROR::InitKeybinds()::Game could not load editor state keybinds config file";
	}

	/*
	* -Create local vars to store file key_bind:key input
	* -Loop through file lines until eof, reading in a key_bind:key map pair
	* -Closes file stream
	*/
	std::string key_bind(""), key("");
	while (ifs >> key_bind >> key)
	{
		this->keyBinds[key_bind] = this->supportedKeys->at(key);
	}

	ifs.close();
}

void PauseState::initGraphics()
{
	
	this->pauseMenuBackground.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->Color->lighterGrey.a = 165;
	this->pauseMenuBackground.setFillColor(this->Color->lighterGrey);
	this->Color->lighterGrey.a = 255;
	this->pauseMenuBackground.setPosition(sf::Vector2f(this->window->getPosition()));

}

void PauseState::initButtons()
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

PauseState::PauseState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f, Fonts& fonts, Colors& color)
	:State(window, supportedKeys, states, grid_size_f), Font(&fonts), Color(&color)
{
	this->isPaused = false;
	this->pauseAction = -1;
	this->initKeybinds();
	this->initButtons();
	this->initGraphics();
}

PauseState::~PauseState()
{
}

void PauseState::togglePaused()
{
	this->isPaused = !this->isPaused;
}

const int& PauseState::getPauseAction()
{
	return this->pauseAction;
}

const bool& PauseState::getPaused() const
{
	return this->isPaused;
}

void PauseState::Update(const float& dt){}

void PauseState::editorUpdate(const float& dt, sf::Vector2f mouse_pos_window)
{
	this->updateMousePos();
	this->updateKeytime(dt);

	this->pauseAction = -1;
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime())
		{
			this->isPaused = false;
		}

		this->updateButtons(mouse_pos_window);
}

void PauseState::updateButtons(sf::Vector2f mouse_pos_window)
{
	for (auto& it : this->buttons)
	{
		it.second->Update(this->mousePosView);
	}

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

void PauseState::Render(sf::RenderTarget* target)
{

	if (!target) { target = this->window; }

	target->draw(this->pauseMenuBackground);
	this->renderButtons(*target);
}

void PauseState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}
