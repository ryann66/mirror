#pragma once

#include <vector>

#include "Scene.hh"
#include "Level.hh"

namespace game {

/**
 * Displays the game scene
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

	friend void gameSceneDisplayFunc();

 private:
	Level* level;
};

inline GameScene* curScene;

}  // namespace game