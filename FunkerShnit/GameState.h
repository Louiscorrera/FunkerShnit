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
	SkillComponent* currPlayerSkill;

	/* Enemies */
	std::vector<Enemy*> activeEnemies;

	/* Tile Map */
	TileMap* tileMap;
	sf::Texture tileMapTextureSheet;

	/* Pause Menu */

	/* Sword Action */
	int swordAction;

	/* Combat */
	CombatSystem combatSystem;
	

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
	void initEnemies();
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
	GameState(StateData* state_data);
	virtual ~GameState();

	/**** ACCESSORS ****/

	/**** METHODS ****/

	/*** Updates ***/
	void Update(const float& dt) override;
	void updatePlayerInput(const float& dt);
	void updateTileMap(const float& dt);
	void updateEnemies(const float& dt);
	void updateView(const float& dt);
	void updatePlayerMovement(const float& dt);
	void updatePlayerWeapon();
	void updateCombat(Player* player, Entity* Enemy1, Entity* Enemy2);

	/*** Renders ***/
	void Render(sf::RenderTarget* target = NULL);
	void renderPlayer(sf::RenderTarget& target);
	void renderTileMap(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
};



#endif // !GAMESTATE_H