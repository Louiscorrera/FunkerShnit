#include "stdafx.h"
#include "Game.h"


/**** METHODS(Private) ****/

/*** Inits ***/
void Game::initVars()
{
	/* Game Clock */
	this->gameClock.restart();

	this->mouseDesktopPos = sf::Mouse::getPosition();
}


void Game::initWindow()
{
	/* Must create state data obj here because it is used in the initializing of the window below */
	this->stateData = new StateData();
	//this->stateData->gfxSettings->loadGfxFromFile("File to load window settins from");

	/* Initialize window using statedata's gfxsettings */
	/* Check if fullscreen or not */
	if (this->stateData->gfxSettings->fullscreen) //Fullscreen
	{
		this->window = new sf::RenderWindow(sf::VideoMode(this->stateData->gfxSettings->resolution), stateData->gfxSettings->title, sf::Style::Titlebar);
		this->window->setFramerateLimit(stateData->gfxSettings->frameRateLimit);
	}
	else //Not fullscreen
	{
		this->window = new sf::RenderWindow(sf::VideoMode(this->stateData->gfxSettings->resolution), this->stateData->gfxSettings->title, sf::Style::Titlebar );
		this->window->setFramerateLimit(this->stateData->gfxSettings->frameRateLimit);
	}

}

void Game::initKeys()
{
	/* Opens an in file stream to read in supported keys for game */
	std::ifstream ifs("Config/supported_keys.txt");
	if (!ifs.is_open())
	{
		throw "ERROR::InitKeybinds()::Game could not load supported keys config file";
	}

	/* 
	* -Create local vars to store file key_bind:key input 
	* -Loop through file lines until eof, reading in a key_bind:key map pair
	* -Closes file stream
	*/
	std::string key_bind = "";
	int key = 0;
	while (ifs >> key_bind >> key)
	{
		this->supportedKeys[key_bind] = key;
	}

	ifs.close();
}

void Game::initStateStack()
{
	this->states.push(new MainMenuState(this->stateData));
}

void Game::initStateData()
{
	this->stateData->states = &this->states;
	this->stateData->window = this->window;
	this->stateData->supportedKeys = &this->supportedKeys;
}





/**** CONSTRUCTOR | DESTRUCTOR ****/

Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStateStack();
	
}


Game::~Game()
{
	delete this->window;
	delete this->stateData;
	
}



/**** Run ****/
const bool& Game::run()
{
	while (this->isRunning())
	{
		this->updateTime();
		this->Update();
		this->Render();
	}
	return false;
}



/**** ACCESSORS ****/

/*** Game States ***/
const bool& Game::isRunning()
{
	return this->window->isOpen();
}



/**** METHODS ****/

/*** Updates ***/
void Game::Update()
{
	/* Update SFML events */
	this->updateSFMLEvents();

	this->updateMousePos();


	/* Check if state stack is empty */
	if (!this->states.empty())
	{
		/* Update current state */
		this->states.top()->Update(this->dt);

		/* Check if current state has been quit */
		if (this->states.top()->getQuit() == true)
		{
			/* Call current states endState() which sets that states data member: quit to true (this is duplicated in State)*/
			this->states.top()->endState();

			/* Delete the current states data then delete the current state's stacks pointer */
			delete this->states.top();
			this->states.pop();
		}
	}
	else //If all states have been exited, the game is over, end application
	{
		/* Close SFML window */
		this->window->close();
	}
	

}


void Game::updateTime()
{
	this->dt = this->gameClock.restart().asSeconds();
}


void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			//this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		/*case sf::Event::TextEntered:
			if (this->ev.text.unicode < 128)
			{
				std::cout << " Text Entered: " << this->ev.text.unicode << "\n";
			}
			break;*/

		default:
			break;
		}
	}
}

void Game::updateMousePos()
{
	this->mouseDesktopPos = sf::Mouse::getPosition(*this->window);


	/* Check if mouse is outside current render window, stop using mouse if so */
	/*if (this->mouseDesktopPos.x > this->window->getSize().x|| this->mouseDesktopPos.x < 0
		|| this->mouseDesktopPos.y > this->window->getSize().y || this->mouseDesktopPos.y < 0)
	{
		this->window->setMouseCursorGrabbed(false);
	}else
	{
		this->window->setMouseCursorGrabbed(true);
	}*/
	
}

/*** Renders ***/
void Game::Render()
{
	/* Clear current windows content */
	this->window->clear(sf::Color::White);

	/* If state stack is not empty, render the current state */
	if (!this->states.empty()) { this->states.top()->Render(this->window); }

	/* Displays current window's content */
	this->window->display();
}










