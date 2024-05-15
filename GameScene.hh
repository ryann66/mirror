#pragma once

#include <vector>

#include "Scene.hh"

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
	GameScene();
	GameScene(const GameScene&) = delete;
	GameScene& operator=(const GameScene&) = delete;
	virtual ~GameScene();

	virtual void onLoad();
	virtual void onUnload();

	friend void gameSceneDisplayFunc();
	friend void gameTick(int);

 private:
};

inline GameScene* curScene;

}  // namespace game