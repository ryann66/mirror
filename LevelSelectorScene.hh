#pragma once

#include <vector>
#include <string>

#include "Scene.hh"
#include "Button.hh"
#include "MenuElement.hh"

namespace menu {

/**
 * Scene for the level selection menu
 * Written in the fixed function style of openGL
*/
class LevelSelectorScene : public Scene {
 public:
	LevelSelectorScene();
	LevelSelectorScene(const LevelSelectorScene&) = delete;
	LevelSelectorScene& operator=(const LevelSelectorScene&) = delete;
	virtual ~LevelSelectorScene();

	virtual void onLoad() = 0;
	virtual void onUnload() = 0;
	
 private:
	Button* scrollbar;
	std::vector<Button*> scrollbarButtons;
	std::vector<MenuElement*> elements;
	std::vector<Button*> buttons;
};

/**
 * Creates a new instance of the level selection menu
 */
Scene* levelSelectorMenu();

}  // namespace menu