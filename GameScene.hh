#pragma once

#include <vector>

#include "Scene.hh"
#include "Map.hh"
#include "Kart.hh"

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
	GameScene(Map* map, std::vector<Kart*> karts) : Scene(GAME, gameSceneDisplayFunc), map(map), karts(karts) { }
	GameScene(const GameScene&) = delete;
	GameScene& operator=(const GameScene&) = delete;
	virtual ~GameScene();

	virtual void onLoad();
	virtual void onUnload();

	friend void gameSceneDisplayFunc();
	friend void gameTick(int);

 private:
	Map* map;
	std::vector<Kart*> karts;
	int frameCount = 0;
};

}  // namespace game