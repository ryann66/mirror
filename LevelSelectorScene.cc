#include "LevelSelectorScene.hh"

#include "Vector2.hh"
#include "LevelButton.hh"

using std::string;

using vector::Vector2;

namespace menu {

// todo write function to get level name from filename

LevelSelectorScene::LevelSelectorScene(const std::vector<Button*> scrollbarButtons) : MenuScene(LEVEL_SELECTOR), scrollbarButtons(scrollbarButtons) {
	// todo require vector of filenames
	// todo setup scrollbar (and fields)
}

LevelSelectorScene::~LevelSelectorScene() {
	// todo (nothing?)
}

void LevelSelectorScene::onLoad() {
	MenuScene::onLoad();
	// todo override mouseFunc to force clicks withing scrollbox
}

Scene* levelSelectorMenu() {
	// get list of levels and make buttons
	// use menu scene if not enough elements to warrant scrolling
}

}  // namespace menu