#pragma once

#include <stdint.h>

enum SceneType {
	MAIN_MENU = 0, PAUSE_MENU, GAME, RESULTS, LEVEL_SELECTOR, ERROR_SCENE
};

/**
 * A scene to be rendered
*/
class Scene {
 public:
	/**
	 * Scene is guaranteed to be loaded before display starts
	*/
	Scene(const SceneType type, void (*displayFunction)()) : type(type), displayFunction(displayFunction) { }
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	virtual ~Scene() { }

	/**
	 * methods to call when scene is loaded and unloaded (pause/unpause) from the forefront
	 * these methods should not produce calls to window to change scene
	 */
	virtual void onLoad() = 0;
	virtual void onUnload() = 0;

	const SceneType type;
	
 protected:
	void (*displayFunction)();
};