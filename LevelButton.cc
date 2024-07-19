#include "LevelButton.hh"

#include <fstream>
#include <stdexcept>

#include "Window.hh"
#include "Vector2.hh"
#include "GameScene.hh"
#include "Level.hh"

using std::string;
using std::ifstream;
using std::exception;
using vector::Vector2;

namespace menu {

string* selectedLevelFilename;

void levelClickFunc() {
	try {
		ifstream levelfile(*selectedLevelFilename);
		window->addScene(new game::GameScene(new game::Level(levelfile)));
		window->loadScene(GAME);
	} catch (exception* e) {
		// todo: add error handling scene
		std::cerr << e->what() << std::endl;
		window->replaceScene(MAIN_MENU);
	}
}

void LevelButton::onClick() {
	selectedLevelFilename = &levelFilename;
	EasyButton::onClick();
}

}  // namespace menu