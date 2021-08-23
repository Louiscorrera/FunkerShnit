#include "stdafx.h"
#include "EditorState.h"

void EditorState::initKeybinds()
{
	/* Opens an in file stream to read in supported keys for game */
	std::ifstream ifs("Config/editorstate_keybinds.txt");
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


void EditorState::initText()
{
	/* Init error message text */
	this->text.setFont(this->stateData->font->marketDeco);
	this->text.setString("Editor State");
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(36.f);
	this->text.setPosition(sf::Vector2f(
		this->stateData->window->getSize().x / 2.f - this->text.getLocalBounds().width /2.f,
		this->stateData->window->getSize().y / 20.f
		));

	/* Init mouse tile info */
	
	this->mouseTileInfo.setFont(this->stateData->font->marketDeco);
	this->mouseTileInfo.setString("Default");
	this->mouseTileInfo.setCharacterSize(24.f);
	this->mouseTileInfo.setFillColor(sf::Color::Black);
	this->mouseTileInfo.setPosition(this->mousePosGrid.x, this->mousePosGrid.y);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(50.f, 50.f, 1.f, this->stateData->gfxSettings->gridSizeF);

	/* Init tile map texture sheet */
	if (!this->tileMapTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.2.png"))
	{
		throw "ERROR::InitTileMap() Could not load tile map texture sheet";
	}
}

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{
	/* Inits a tileMap tile selector */
	this->tileSelectorGuide.setSize(sf::Vector2f(this->stateData->gfxSettings->gridSizeF, this->stateData->gfxSettings->gridSizeF));
	this->tileSelectorGuide.setOutlineThickness(3.f);
	this->tileSelectorGuide.setOutlineColor(sf::Color::Magenta);
	this->tileSelectorGuide.setTexture(&this->tileMapTextureSheet);

	/* Init texture selector intRect*/
	this->textureSelector = sf::IntRect(0, 0, static_cast<int>(this->stateData->gfxSettings->gridSizeF), static_cast<int>(this->stateData->gfxSettings->gridSizeF));

	this->tileSelectorGuide.setTextureRect(this->textureSelector);
	this->tileSelectorGuide.setFillColor(sf::Color(0, 0, 0, 150));

	/* Inits user error message font and text */
	this->initText();
	this->initButtons();

	/* Inits tile map texure selector interface */
	this->tileMapTextureSelector = new gui::EditorTextureSelector(20.f, 50.f, 450.f, 500.f, this->stateData->gfxSettings->gridSizeF, &this->tileMapTextureSheet, this->stateData->font, this->stateData->color);
}

void EditorState::initView()
{
	this->mainView.setSize(sf::Vector2f(this->stateData->window->getSize().x, this->stateData->window->getSize().y));

	this->mainView.setCenter(this->stateData->window->getSize().x / 2.f, this->stateData->window->getSize().y / 2.f);
}

void EditorState::initPauseMenu()
{
	this->pauseMenu = new gui::PauseMenu(this->stateData->window, this->stateData->font, this->stateData->color);
}

void EditorState::initSounds()
{
	if (!this->buffer.loadFromFile("Resources/Sound/Click.wav"))
	{
		throw "ERROR::InitSounds()::EDITORSTATE could not load one or more of the sound buffers ";
	}
	if (!this->mainMusic.openFromFile("Resources/Sound/editorstate_mainmusic.wav"))
	{
		throw "ERROR::InitSounds()::EDITORSTATE could not load one or more of the sound buffers ";
	}

	this->click.setBuffer(this->buffer);
	
}


EditorState::EditorState(StateData* state_data)
	:State(state_data)// pauseMenu(NULL)
{
	this->initKeybinds();
	this->initView();
	this->initTileMap();
	this->initGui();
	this->initPauseMenu();
	this->initSounds();

	this->keyTime = 0.f;
	this->keyTimeMax = 15.f;
	
}

EditorState::~EditorState()
{
	
}

void EditorState::Update(const float& dt)
{
	//system("cls");
	//std::cout << "F_Window_X: " << this->mousePosWindow.x << " F_Window_Y: " << this->mousePosWindow.y;

		
		this->updateKeytime(dt);


		if (this->pauseMenu->getPaused() == true)
		{
			this->updateMousePos();
			this->mainMusic.pause(); //Pause music
			this->pauseMenu->Update(dt, this->mousePosView);
			this->updatePauseMenuAction();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("PAUSE"))) && this->getKeyTime())
			{
				this->pauseMenu->togglePaused();
			}
		
		}
		else
		{
			/* Check is music is not already playing music */
			if (this->mainMusic.getStatus() != sf::Music::Playing)
			{
				/* Set music on loop */
				this->mainMusic.setVolume(40.f);
				this->mainMusic.setLoop(true);
				this->mainMusic.play();
			}

			
			this->updateMousePos(&this->mainView);
		
			this->updateView();
		
			this->updateGui(dt);
			
			this->updateEditorInput();
			
			this->updateMouseTileInfo();
			
			this->updateButtons(); //Empty right now, leaving bc i may use later :)
		}
	
		
}

	
	
	



void EditorState::updateEditorInput()
{
	
	/* If the texture selector interface is hidden enable adding/removing tiles ()*/
	if (this->tileMapTextureSelector->getHidden() == true)
	{
		if (this->mousePosWindow.x > 100 || this->mousePosWindow.y > 50) /* If the cursor is not within the bounds of the "Hide/Show" button, enable adding/removing tiles()()*/
		{
			/* If left mouse is clicked, attempt to add tile */
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
			{ 
				/* Check if collision is enabled, add a collision tile if so */
				if (this->tileMap->getCollision())
				{
					/* Display tile added confirmation message if tile was added */
					if (this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->tileMapTextureSheet, this->textureSelector, true, this->tileMap->getTileType()))
					{
						this->click.play(); //Click into place fx
						this->text.setString("Tile Added!"); //attempt status displayed to user
					}
					else /* Display tile can't be added message if tile is full */
					{
						this->text.setString("Tile Full!"); //attempt status displayed to user
					}
				}
				else /* Check if collision is disabled, add a regular tile (non-collision) if so */
				{
					/* Display tile added confirmation message if tile was added */
					if (this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->tileMapTextureSheet, this->textureSelector, false, this->tileMap->getTileType()))
					{
						this->click.play(); //Click into place fx
						this->text.setString("Tile Added!"); //attempt status displayed to user
					}
					else /* Display tile can't be added message if tile is full */
					{
						this->text.setString("Tile Full!"); //attempt status displayed to user
					}
				}

			}
			/* If mouse right click, attempt to remove tile */
			else  if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
			{
				/* Display tile removed confirmation message if tile was removed */
				if (this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0))
				{
					this->text.setString("Tile Removed!"); //attempt status displayed to user 
				}
				else /* Display tile can't be removed if there is no tile to remove */
				{
					this->text.setString("No Tile to Remove!"); //attempt status displayed to user 
				}

			}
			else{} /* If neither left or right click is pressed don't do anything */
		}else{} /* If the cursor is not within the bounds of the "Hide/Show" button, disable adding/removing tiles ()()*/
	}else{}/* If the texture selector interface is open disable adding/removing tiles ()*/
	
	

	/* check if the quit button has been pressed, end game state if so */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime())
	{
		this->endState();
	}

	/* Toggle tile map overwrite capabilities */
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TOGGLE_OVERWRITE"))) && this->getKeyTime())
	{
		this->tileMap->toggleOverwrite();
	}*/

	/* Toggle Tile-to-add's collision (Enabled | Disabled) */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TOGGLE_COLLISION"))) && this->getKeyTime())
	{
		this->tileMap->toggleCollision();
	}

	/* Toggle Tile-to-add's type (Cycles)__See Tile.h for enum types) */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TOGGLE_TYPE"))) && this->getKeyTime())
	{
		this->tileMap->toggleType();
	}

	/* Toggle Tile-to-add's enemy type, if enemy spawner is enabled (Cycles)__See Tile.h for enum types) */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TOGGLE_ENEMY_TYPE"))) && this->getKeyTime())
	{
		this->tileMap->toggleEnemyType();
	}

	/* Pause menu */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("PAUSE"))) && this->getKeyTime())
	{
		this->pauseMenu->togglePaused();
	}

	if (this->tileMap->getEnemyType() == EnemyType::ENEMY3)
	{

	}
}




void EditorState::updateButtons()
{
	
}

void EditorState::updateGui(const float& dt)
{
	/* Update texture selector every iteration because hide/revel button is in that class, and this allows the check of it being pressed to happen */
	this->tileMapTextureSelector->Update(this->mousePosWindow, dt);

	/* 
	* If the texture selector window is hidden 
	* -Update the tilemap tile selector
	* -Set the texture to add to tiles to its current texture rectangle
	*/
	if (this->tileMapTextureSelector->getHidden() == true)
	{
	
		this->tileSelectorGuide.setPosition(this->mousePosGrid.x * this->stateData->gfxSettings->gridSizeF, this->mousePosGrid.y * this->stateData->gfxSettings->gridSizeF);
		this->tileSelectorGuide.setTexture(&this->tileMapTextureSheet);
		this->tileSelectorGuide.setTextureRect(this->textureSelector);
		this->tileSelectorGuide.setOutlineColor(this->stateData->color->lightGreen);
	}
	else /*
		 * If texture selector window is NOT hidden
		 * -check if the mouse is within the texture selector interface
		 * -update texture if
		 */

	{
		/* If mouse is not within texture selector*/
		if (!this->tileMapTextureSelector->getActive())
		{
			/* Update tileMap tile selector position to the grid mouse position */
			this->tileSelectorGuide.setPosition(this->mousePosGrid.x * this->stateData->gfxSettings->gridSizeF, this->mousePosGrid.y * this->stateData->gfxSettings->gridSizeF);

		}

		/* Update texture selected */
		this->tileSelectorGuide.setTexture(&this->tileMapTextureSheet);
		this->tileSelectorGuide.setTextureRect(this->textureSelector);
		this->tileSelectorGuide.setOutlineColor(this->stateData->color->darkRed);
		this->textureSelector = this->tileMapTextureSelector->getTextureRect();
	}
	
	
}

void EditorState::updateMouseTileInfo()
{
	std::stringstream ss;
	std::string type;
	std::string enemyType;

	if (this->tileMap->getEnemySpawner())
	{
		if (this->tileMap->getEnemyType() == EnemyType::ENEMY1) 
		{ 
			enemyType = "Enemy type 1"; 
		}
		if (this->tileMap->getEnemyType() == EnemyType::ENEMY2) 
		{ 
			enemyType = "Enemy type 2"; 
		}
		if (this->tileMap->getEnemyType() == 2) 
		{
			enemyType = "Enemy type 3"; 
		}
	}

	if (this->tileMap->getEnemyType() == EnemyType::ENEMY3)
	{
		std::cout << "\n";
	}

	if (this->tileMap->getTileType() == 0) { type = "REGULAR"; }
	if (this->tileMap->getTileType() == 1) { type = "COLLISION"; }
	if (this->tileMap->getTileType() == 2) { type = "DEFERRED"; }
	if (this->tileMap->getTileType() == 3) { type = "DAMAGE"; }
	if (this->tileMap->getTileType() == 4) { type = "ANIMATION"; }
	if (this->tileMap->getTileType() == 5) { type = "ENEMY"; }

	ss << "(" << this->mousePosGrid.x << ", " << this->mousePosGrid.y << ")" << 
		"\n" << "Collision: " << ((this->tileMap->getCollision()) ? "Enabled" : "Disabled") << " (C to toggle) " <<
		"\n" << "Type: " << type << " (V to toggle) " ;
	if (this->tileMap->getEnemySpawner()) { ss << "\n" << "Enemy Type: " << enemyType << " (B to toggle) "; }

	this->mouseTileInfo.setString(ss.str());
	this->mouseTileInfo.setPosition(this->mousePosWindow.x + 60.f, this->mousePosWindow.y);
}

void EditorState::updateView()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAM_UP"))))
	{
		this->mainView.move(sf::Vector2f(0.f, -10.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAM_DOWN"))))
	{
		this->mainView.move(sf::Vector2f(0.f, 10.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAM_LEFT"))))
	{
		this->mainView.move(sf::Vector2f(-10.f, 0.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAM_RIGHT"))))
	{
		this->mainView.move(sf::Vector2f(10.f, 0.f));
	}
}

void EditorState::updatePauseMenuAction()
{
	if (this->pauseMenu->getPauseAction() == gui::PauseMenuAction::SAVE)
	{
		this->tileMap->saveTileMap("Test.txt");
	}
	if (this->pauseMenu->getPauseAction() == gui::PauseMenuAction::LOAD)
	{
		this->tileMap->loadTileMap("Test.txt");
	}
	if (this->pauseMenu->getPauseAction() == gui::PauseMenuAction::CLEAR)
	{
		this->tileMap->clearCurrentMap();
	}
	
}




void EditorState::Render(sf::RenderTarget* target)
{
	/* If there target is NULL set target to current window */
	if (!target) { target = this->stateData->window; }

	/* Check if paused and render pause menu if it is */
	if (this->pauseMenu->getPaused())
	{
		target->setView(this->stateData->window->getDefaultView());
		this->renderTileMap(*target);
		this->pauseMenu->Render(target);
	}
	else
	{
		target->setView(this->mainView);

		this->renderTileMap(*target);

		target->setView(this->stateData->window->getDefaultView());

		this->renderGui(*target);
		this->renderButtons(*target); //Empty, see note on updateButtons() above ^^

	}

	
}

void EditorState::renderTileMap(sf::RenderTarget& target)
{

	/* Renders current tile map */
	this->tileMap->Render(target);
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	
}

void EditorState::renderGui(sf::RenderTarget& target)
{

	/* Renders the texture selector to window */
	target.setView(this->stateData->window->getDefaultView());
	this->tileMapTextureSelector->Render(target);
	

	if (this->tileMapTextureSelector->getHidden() == true)
	{
		if (this->mousePosWindow.x > 100 || this->mousePosWindow.y > 50)
		{
			/* Renders the tile selector */
			target.setView(this->mainView);
			target.draw(this->tileSelectorGuide);
		}
		else
		{

		}
		
		/* Renders user error message text */ //TODO:Add some kind of message display timer
		target.setView(this->stateData->window->getDefaultView());
		target.draw(this->text);

	}
	else
	{
		/* Checks if mouse within textur selector and stops rendering map tile selector guide if so (to ensure only the textureSelector's texture selector guide is actively rendered */
		if (!this->tileMapTextureSelector->getActive())
		{
			if (this->mousePosWindow.x > 100 || this->mousePosWindow.x < 0|| this->mousePosWindow.y > 50)
			{
				/* Renders the tile selector */
				target.setView(this->mainView);
				target.draw(this->tileSelectorGuide);
			}
		}

	}
	
	target.draw(this->mouseTileInfo);
}
