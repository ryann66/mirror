#include "LevelSelectorScene.hh"

#include <filesystem>
#include <stdexcept>

#include "Vector2.hh"
#include "Level.hh"
#include "LevelButton.hh"
#include "Label.hh"

using std::string;
using std::logic_error;

using std::filesystem::directory_iterator;
using std::filesystem::directory_entry;

using vector::Vector2;

namespace menu {

// todo write function to get level name from filename

LevelSelectorScene::LevelSelectorScene(const std::vector<Button*>& scrollbarButtons) : MenuScene(LEVEL_SELECTOR), scrollbarButtons(scrollbarButtons) {
	// todo require vector of filenames
	// todo setup scrollbar (and fields)
}

LevelSelectorScene::~LevelSelectorScene() {
	for (Button* sb : scrollbarButtons) delete sb;
}

void LevelSelectorScene::onLoad() {
	MenuScene::onLoad();
	// todo override mouseFunc to force clicks within scrollbox
}

Scene* levelSelectorMenu() {
	// get list of levels and make buttons
	std::vector<Button*> levelButtons;
	Vector2 offset(0, -(scrollbarHeight / 2) * DEFAULT_BUTTON_SIZE.y);
	const int labelY = offset.y - DEFAULT_BUTTON_SIZE.y;
	for (directory_entry file : directory_iterator("./levels")) {
		if (!file.is_regular_file()) continue;
		LevelButton* level = new LevelButton(offset, game::levelNameFromFilename(file.path()), file.path().string());
		levelButtons.push_back(level);
		offset.y += DEFAULT_BUTTON_SIZE.y;
	}

	// create scene to display (use menu scene if not enough to require scrollbar)
	MenuScene* retscene;
	if (levelButtons.size() <= scrollbarHeight) {
		if (levelButtons.empty()) throw new logic_error("No levels found");
		retscene = new MenuScene(LEVEL_SELECTOR);
		for (Button* lb : levelButtons) retscene->addButton(lb);
	} else {
		retscene = new LevelSelectorScene(levelButtons);
	}

	// add common labels
	offset.y = labelY;
	retscene->addElement(new Label(CENTER, offset, "Select a level", MenuLabelColor));

	return retscene;
}

}  // namespace menu