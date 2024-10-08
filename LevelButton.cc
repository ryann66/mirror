#include "LevelButton.hh"

#include <fstream>
#include <stdexcept>

#include "Window.hh"
#include "Vector2.hh"
#include "GameScene.hh"
#include "Level.hh"
#include "ErrorScene.hh"

using std::string;
using std::ifstream;
using std::exception;
using vector::Vector2;

namespace menu {

string* selectedLevelFilename;

void levelClickFunc() {
	ifstream levelfile(*selectedLevelFilename);
	window->addScene(new game::GameScene(new game::Level(levelfile)));
	window->loadScene(GAME);
}

void LevelButton::onClick() {
	selectedLevelFilename = &levelFilename;
	EasyButton::onClick();
}

}  // namespace menu