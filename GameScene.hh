#pragma once

#include <vector>

#include "Scene.hh"
#include "Map.hh"
#include "Kart.hh"

namespace game {

class GameScene : public Scene {
 public:
	GameScene(Map* map, std::vector<Kart> karts);
	GameScene(const GameScene&) = delete;
	GameScene& operator=(const GameScene&) = delete;
	virtual ~GameScene();

	virtual void onLoad();
	virtual void onUnload();

 private:
	Map* map;
	std::vector<Kart> karts;
};

}  // namespace game