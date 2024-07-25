#pragma once

#include <vector>
#include <string>

#include "MenuScene.hh"
#include "Button.hh"
#include "MenuElement.hh"

namespace menu {

// number of buttons visible at a time
const int scrollbarHeight = 7;

/**
 * Scene for the level selection menu
 * Written in the fixed function style of openGL
*/
class LevelSelectorScene : public MenuScene {
 public:
	LevelSelectorScene(const std::vector<Button*>& scrollbarButtons);
	LevelSelectorScene(const LevelSelectorScene&) = delete;
	LevelSelectorScene& operator=(const LevelSelectorScene&) = delete;
	virtual ~LevelSelectorScene();

	virtual void onLoad();

 private:
	Button* scrollbar;
	const std::vector<Button*> scrollbarButtons;
};

/**
 * Creates a new instance of the level selection menu
 */
Scene* levelSelectorMenu();

}  // namespace menu