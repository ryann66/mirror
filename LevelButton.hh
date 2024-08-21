#pragma once

#include <string>

#include "MenuScene.hh"
#include "MenuElement.hh"
#include "Button.hh"

namespace menu {

void levelClickFunc();

class LevelButton : public EasyButton {
 public:
	LevelButton(const vector::Vector2 offset, std::string levelName, std::string levelFilename) :
		EasyButton(CENTER, offset, DEFAULT_BUTTON_SIZE, levelName, levelClickFunc),
		levelFilename(levelFilename) { }

	LevelButton(const LevelButton&) = delete;
	LevelButton& operator=(const LevelButton&) = delete;

	virtual void onClick();

 private:
	std::string levelFilename;
};

}  // namespace menu
