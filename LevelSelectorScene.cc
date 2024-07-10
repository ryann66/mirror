#include "LevelSelectorScene.hh"

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

void firstLevelPlayClickFunc() {
	try {
		ifstream levelfile("./levels/level1.txt");
		window->addScene(new game::GameScene(new game::Level(levelfile)));
		window->loadScene(GAME);
	} catch (exception* e) {
		std::cerr << e->what() << std::endl;
		window->replaceScene(MAIN_MENU);
	}
}

Scene* levelSelectorMenu() {
	// TODO actually write a level selector menu scene
	MenuScene* menu = new MenuScene(LEVEL_SELECTOR);
	menu->addButton(new EasyButton(CENTER, Vector2(), DEFAULT_BUTTON_SIZE, "level1", firstLevelPlayClickFunc));
	return menu;
}

}  // namespace menu