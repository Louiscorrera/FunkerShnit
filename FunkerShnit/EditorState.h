#ifndef EDITORSTATE_H
#define EDITORSTATE_H



#include "PauseState.h"

class EditorState : public State
{
private:
	/**** DATA MEMBERS ****/

	/* Tile Map */
	TileMap* tileMap;

	/* Texture Selector */
	gui::EditorTextureSelector* tileMapTextureSelector;
	sf::RectangleShape tileSelectorGuide;
	sf::IntRect textureSelector;

	/* Tile Textures */
	sf::Texture tileMapTextureSheet;
	sf::SoundBuffer buffer;
	sf::Sound click;
	sf::Music mainMusic;

	/* Errors */
	sf::Text text;

	/* Mouse */
	sf::Text mouseTileInfo;

	/* Pause Menu */
	PauseState* pauseMenu;

	/* View */
	sf::View mainView;

	/**** METHODS(Private) ****/
	/*** Inits(Pure-Virtuals) ***/
	void initKeybinds() override;
	/*** (Non_Pure Virtuals) ***/
	void initText();
	void initTileMap();
	void initButtons();
	void initGui();
	void initView();
	void initPauseMenu();
	void initSounds();


protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, float grid_size_f);
	virtual ~EditorState();

	/**** ACCESSORS ****/

	/**** METHODS ****/

	/*** Updates ***/
	void Update(const float& dt);
	void updateEditorInput();
	void updateButtons();
	void updateGui(const float& dt);
	void updateMouseTileInfo();
	void updateView();
	void updatePauseMenu();
	

	/*** Renders ***/
	void Render(sf::RenderTarget* target = NULL);
	void renderTileMap(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	
};


#endif //!EDITORSTATE_H