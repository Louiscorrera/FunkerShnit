#include "stdafx.h"
#include "GameState.h"



void GameState::initKeybinds()
{
	/* Opens an in file stream to read in supported keys for game */
	std::ifstream ifs("Config/gamestate_keybinds.txt");
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

void GameState::initDeferredRender()
{


}

void GameState::initPlayer()
{
	/* Load player graphic from file, throw if not opened */
	if (!this->playerGraphic.loadFromFile("Resources/Images/Sprites/Player/diaperBoy.png"))
	{
		throw "ERROR::InitPlayers()::GAMESTATE could not load player graphic image ";
	}

	/* Init Player */
	this->player = new Player(0, 0, this->playerGraphic);
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseState(this->window, this->supportedKeys, this->states, this->grifSizeF, *this->font, *this->color);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(50.f, 50.f, 10.f, this->grifSizeF);

	/* Init tile map texture sheet */
	if (!this->tileMapTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.2.png"))
	{
		throw "ERROR::InitTileMap() Could not load tile map texture sheet";
	}

	this->tileMap->loadTileMap("Test.txt");
}

void GameState::initView()
{
	this->mainView.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));

	this->mainView.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}

void GameState::initGui()
{
	this->initText();
	this->initButtons();
	this->initSounds();
}
void GameState::initButtons()
{

}

void GameState::initText()
{
	
}

void GameState::initSounds()
{
	if (!this->gameMusic.openFromFile("Resources/Sound/editorstate_mainmusic.wav"))
	{
		throw "ERROR::InitSounds()::GAMESTATE could not load main music file ";
	}
	this->gameMusic.setVolume(35.f);
	this->gameMusic.setLoop(true);
	this->gameMusic.play();
}


GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f)
	:State(window, supportedKeys, states, grid_size_f)
{
	this->initKeybinds();
	this->initTileMap();
	this->initPauseMenu();
	this->initView();
	this->initPlayer();
	this->initGui(); // initText() -> initButtons() -> initSounds()

	/* State Changes */
	this->keyTimeMax = 50.f;
	this->keyTime = 0.f;

}

GameState::~GameState()
{
	delete this->tileMap;
	delete this->player;
	delete this->pauseMenu;
}

void GameState::Update(const float& dt)
{
	this->updateMousePos(&this->mainView);
	this->updateKeytime(dt);
	
	/* Updates velocity based off user's input (WASD) */
	this->updatePlayerInput(dt); 

	
	
	this->tileMap->checkTileCollision(dt, this->player);
	/* Applies physics to Velocity
	* Updates player animation based on player movement
	* checks for player sound triggers/manages playing & stopping player sounds
	* Updates hitbox position, relative to player sprite */
	this->player->Update(dt, static_cast<sf::Vector2i>(this->mousePosView));
	this->updateView(dt);
}

void GameState::updatePlayerInput(const float& dt)
{
	/* Updates velocity based of user's input (WASD) */
	float movementSpeed = 1;//Local velocity manipulation factor for ease of changing for me :)

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
	{
		this->player->updateVelocity(0.f, -movementSpeed, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
	{
		this->player->updateVelocity(0.f, movementSpeed, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
	{
		this->player->updateVelocity(-movementSpeed, 0.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
	{
		this->player->updateVelocity(movementSpeed, 0.f, dt);
	}

	/* check if the quit button has been pressed, end game state if so */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))))
	{
		this->endState(); 
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("EQUIP"))) && this->getKeyTime())
	{
		this->player->toggleSwordEquip();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("ATTACK"))) && this->getKeyTime())
	{
		this->player->toggleAttacking();
	}

}

void GameState::updateTileMap(const float& dt)
{
	
}

void GameState::updateView(const float& dt)
{
	this->mainView.setCenter(this->player->getPosition());

	if (this->tileMap->getTileMapMaxSize().x >= this->mainView.getSize().x)
	{
		if (this->mainView.getCenter().x - this->mainView.getSize().x / 2.f < 0.f)
		{
			this->mainView.setCenter(0.f + this->mainView.getSize().x / 2.f, this->mainView.getCenter().y);
		}
		else if (this->mainView.getCenter().x + this->mainView.getSize().x / 2.f > this->tileMap->getTileMapMaxSize().x)
		{
			this->mainView.setCenter(this->tileMap->getTileMapMaxSize().x - this->mainView.getSize().x / 2.f, this->mainView.getCenter().y);
		}
	}

	if (this->tileMap->getTileMapMaxSize().y >= this->mainView.getSize().y)
	{
		if (this->mainView.getCenter().y - this->mainView.getSize().y / 2.f < 0.f)
		{
			this->mainView.setCenter(this->mainView.getCenter().x, 0.f + this->mainView.getSize().y / 2.f);
		}
		else if (this->mainView.getCenter().y + this->mainView.getSize().y / 2.f > this->tileMap->getTileMapMaxSize().y)
		{
			this->mainView.setCenter(this->mainView.getCenter().x, this->tileMap->getTileMapMaxSize().y - this->mainView.getSize().y / 2.f);
		}
	}
	
	//this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->grifSizeF);
	//this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->grifSizeF);
	

}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target) { target = this->window; }

	target->setView(this->mainView);
	this->renderTileMap(*target);
	this->renderPlayer(*target);
	this->tileMap->deferredRender(*target);
	
}

void GameState::renderPlayer(sf::RenderTarget& target)
{
	this->player->Render(target);
}

void GameState::renderTileMap(sf::RenderTarget& target)
{
	this->tileMap->Render(target, &this->player->getEntitySprite());
}
