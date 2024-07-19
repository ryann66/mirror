#include "LevelSelectorScene.hh"

#include "Vector2.hh"
#include "LevelButton.hh"

using std::string;

using vector::Vector2;

namespace menu {

LevelSelectorScene::LevelSelectorScene() : MenuScene(LEVEL_SELECTOR) {
	// todo
}

LevelSelectorScene::~LevelSelectorScene() {
	// todo
}

void LevelSelectorScene::onLoad() {
	// todo
}

void LevelSelectorScene::onUnload() {
	// todo
}

Scene* levelSelectorMenu() {
	return new LevelSelectorScene;
}

}  // namespace menu