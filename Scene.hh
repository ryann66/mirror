#pragma once

#include <stdint.h>

enum SceneType : uint8_t {
	MAIN_MENU = 0, PAUSE_MENU, GAME, RESULTS
};

/**
 * A scene to be rendered
*/
class Scene {
 public:
	/**
	 * Scene is guaranteed to be loaded before display starts
	*/
	Scene(const SceneType type, const void (*displayFunction)()) : type(type), displayFunction(displayFunction) { }
	Scene(const Scene&) = delete;
	virtual ~Scene() { }

	/**
	 * methods to call when scene is loaded and unloaded (pause/unpause) from the forefront
	 * these methods should not produce calls to window to change scene
	 */
	virtual void onLoad() = 0;
	virtual void onUnload() = 0;

	/**
	 * returns true if the scene should be destroyed by the window manager on returning
	*/
	bool destroyable() const { return destroy; }

	/**
	 * returns what kind of scene this is
	*/
	SceneType getType() const { return type; }

 protected:
	const SceneType type;
	const void (*displayFunction)();
	bool destroy = false;
};