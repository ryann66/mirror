#pragma once

#include <vector>

#include "Scene.hh"
#include "Level.hh"

namespace game {

/**
 * Displays the game scene, checks win condition
*/
void gameSceneDisplayFunc();

class GameScene : public Scene {
 public:
	/**
	 * Constructs a new game scene
	 * Takes ownership of map
	*/
	GameScene(Level* level) : Scene(GAME, gameSceneDisplayFunc), level(level) { }
	GameScene(const GameScene&) = delete;
	GameScene& operator=(const GameScene&) = delete;
	virtual ~GameScene();

	virtual void onLoad();
	virtual void onUnload();

	Level* const level;
};

}  // namespace game