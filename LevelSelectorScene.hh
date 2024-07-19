#pragma once

#include <vector>
#include <string>

#include "MenuScene.hh"
#include "Button.hh"
#include "MenuElement.hh"

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

	virtual void onLoad();
	virtual void onUnload();

 private:
	Button* scrollbar;
	std::vector<Button*> scrollbarButtons;
};

/**
 * Creates a new instance of the level selection menu
 */
Scene* levelSelectorMenu();

}  // namespace menu