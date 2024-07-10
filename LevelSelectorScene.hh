#pragma once

#include <list>
#include <string>

#include "Scene.hh"
#include "Button.hh"
#include "MenuScene.hh"

namespace menu {

/**
 * Scene for the level selection menu
 * Written in the fixed function style of openGL
*/
class LevelSelectorScene : public MenuScene {
 public:
	LevelSelectorScene();
	LevelSelectorScene(const LevelSelectorScene&) = delete;
	LevelSelectorScene& operator=(const LevelSelectorScene&) = delete;
	virtual ~LevelSelectorScene();

 private:
	std::list<std::string> levels;
};

/**
 * Creates a new instance of the level selection menu
 */
Scene* levelSelectorMenu();

}  // namespace menu