#pragma once

#include <string>

#include "Scene.hh"

namespace menu {

/**
 * Scene for automatically redirecting to an error
 */
class EmptyLevelSelectorScene : public Scene {
 public:
	EmptyLevelSelectorScene() : Scene(LEVEL_SELECTOR, nullptr) { }
	EmptyLevelSelectorScene(const EmptyLevelSelectorScene&) = delete;
	EmptyLevelSelectorScene& operator=(const EmptyLevelSelectorScene&) = delete;
	virtual ~EmptyLevelSelectorScene() { }

	virtual void onLoad() { newErrorScene("No levels found"); }
	virtual void onUnload() { }
};


}  // namespace menu