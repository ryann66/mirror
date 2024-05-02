#pragma once

#include <unordered_map>
#include <stdint.h>

#include "Scene.hh"

/**
 * Manager class for the whole window
 * Only one of each scene type can exist at a time
*/
class Window {
 public:
	/**
	 * creates a new manager and loads the mainScene
	 * takes over memory management of scene
	 * NOTE: loading mainScene may produce calls that require glut initialization
	*/
	Window(Scene* mainScene);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();

	/**
	 * loads the given scene
	 * throws logic error if scene is not created
	*/
	void loadScene(SceneType);

	/**
	 * adds the given scene, taking over memory management as well
	 * throws logic error if the scene type is already defined
	 * NOTE: it is scene's responsibility to mark themselves as deletable
	 *       so they can be removed and replaced
	*/
	void addScene(Scene*);

 private:
	std::unordered_map<SceneType, Scene*> scenes;
	SceneType activeScene;
};

void closeFunction() {
	// TODO delete the window
}