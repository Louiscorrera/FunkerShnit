#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "EditorState.h"

class PauseState;


class GameState : public State
{
private:
	/**** DATA MEMBERS ****/

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	/* Player */
	Player* player;
	sf::Texture playerGraphic;

	/* Tile Map */
	TileMap* tileMap;
	sf::Texture tileMapTextureSheet;

	/* Pause Menu */
	PauseState* pauseMenu;

	/* View */
	sf::View mainView;

	/* Music | Sound */
	sf::Music gameMusic;


	/**** METHODS(Private) ****/
	/*** Inits ***/
	/** Pure Virtuals **/
	void initKeybinds() override;
	/** (Non_Pure Virtuals) **/
	void initDeferredRender();
	void initPlayer();
	void initPauseMenu();
	void initTileMap();
	void initView();
	void initGui(); // Empty
	void initButtons(); // Empty
	void initText(); // Empty
	void initSounds(); // Empty

protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f);
	virtual ~GameState();

	/**** ACCESSORS ****/

	/**** METHODS ****/

	/*** Updates ***/
	void Update(const float& dt) override;
	void updatePlayerInput(const float& dt);
	void updateTileMap(const float& dt);
	void updateView(const float& dt);

	/*** Renders ***/
	void Render(sf::RenderTarget* target = NULL);
	void renderPlayer(sf::RenderTarget& target);
	void renderTileMap(sf::RenderTarget& target);
};



#endif // !GAMESTATE_H