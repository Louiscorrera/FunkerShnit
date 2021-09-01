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
		this->keyBinds[key_bind] = this->stateData->supportedKeys->at(key);
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
	this->player = new Player(0, 0, this->playerGraphic, 100);
}

void GameState::initEnemies()
{
	this->activeEnemies.reserve(1);
}

void GameState::initPauseMenu()
{
	//this->pauseMenu = new PauseState(this->stateData);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(25.f, 25.f, 10.f, this->stateData->gfxSettings->gridSizeF);

	/* Init tile map texture sheet */
	if (!this->tileMapTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.2.png"))
	{
		throw "ERROR::InitTileMap() Could not load tile map texture sheet";
	}

	this->tileMap->loadTileMap("Test.txt");
}

void GameState::initView()
{
	this->mainView.setSize(sf::Vector2f(this->stateData->window->getSize().x, this->stateData->window->getSize().y));

	this->mainView.setCenter(this->stateData->window->getSize().x / 2.f, this->stateData->window->getSize().y / 2.f);
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
	//this->gameMusic.setVolume(35.f);
	//this->gameMusic.setLoop(true);
	//this->gameMusic.play();
}


GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initKeybinds();
	this->initTileMap();
	this->initEnemies();
	this->initPauseMenu();
	this->initView();
	this->initPlayer();
	this->initGui(); // initText() -> initButtons() -> initSounds()

	/* State Changes */
	this->keyTimeMax = 50.f;
	this->keyTime = 0.f;

	this->swordAction = SwordAttack::DEFAULT;

	

}

GameState::~GameState()
{
	delete this->tileMap;
	delete this->player;
	
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
	this->player->Update(dt, static_cast<sf::Vector2i>(this->mousePosView), this->swordAction);

	this->updateEnemies(dt);

	this->updateView(dt);
}

void GameState::updatePlayerInput(const float& dt)
{
	/* check if the quit button has been pressed, end game state if so */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))))
	{
		this->endState(); 
	}

	this->updatePlayerMovement(dt); //Update movement
	this->updatePlayerWeapon(); //Update weapon
	

}

void GameState::updateTileMap(const float& dt)
{
	
}

void GameState::updateEnemies(const float& dt)
{
	this->tileMap->checkEnemySpawners(dt, &this->activeEnemies, this->player);

	for (int i = 0; i < this->activeEnemies.size(); i++)
	{
		this->combatSystem.battle(*this->player, *this->activeEnemies[i]);
		if (!this->activeEnemies[i]->getIsAlive())
		{
			this->activeEnemies[i]->despawn();
			this->activeEnemies.erase(this->activeEnemies.begin() + i);
		}
		else
		{
			this->activeEnemies[i]->Update(dt, this->player);
			this->tileMap->checkTileCollision(dt, this->activeEnemies[i]);
		}
		
		
	}
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

void GameState::updatePlayerMovement(const float& dt)
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
}

void GameState::updatePlayerWeapon()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("EQUIP"))) && this->getKeyTime())
	{
		this->player->toggleSwordEquip();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("ATTACK"))) && this->getKeyTime())
	{
		this->player->toggleAttacking();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		this->player->attackStab();
	}
	
}

void GameState::updateCombat(Player* player, Entity* Enemy1, Entity* Enemy2)
{
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target) { target = this->stateData->window; }

	target->setView(this->mainView);
	this->renderTileMap(*target);
	this->renderPlayer(*target);
	this->renderEnemies(*target);
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

void GameState::renderEnemies(sf::RenderTarget& target)
{
	for (int i = 0; i < this->activeEnemies.size(); i++)
	{
		this->activeEnemies[i]->Render(target);
	}
}
