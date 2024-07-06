#pragma once

#include <unordered_map>
#include <stdint.h>

#include "Scene.hh"
#include "Vector2.hh"

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
	 * throws logic error if scene is not defined
	*/
	void loadScene(SceneType);

	/**
	 * adds the given scene, taking over memory management as well
	 * throws logic error if the scene type is already defined
	*/
	void addScene(Scene*);

	/**
	 * Deletes the given scene, freeing all memory associated with it
	 * throws logic error if the scene is not defined
	 * throws logic error if this is the loaded scene
	*/
	void deleteScene(SceneType);

	/**
	 * Deletes the current scene (freeing memory) and loads the given scene
	 * throws logic error if the scene is not defined
	 * throws logic error if the scene type is currently loaded
	*/
	void replaceScene(SceneType);

	vector::Vector2 size;	

 private:
	std::unordered_map<SceneType, Scene*> scenes;
	SceneType activeScene;
};

// pointer to the main window
inline Window* window;

/**
 * Forces program closure
*/
void closeFunction();

/**
 * Dummy function to provide to unregistering glutDisplayFunc
 * Should never be called, indicates error
*/
void unregisteredDisplayFunc();

/**
 * Converts X/Y coords from glut coordinate system to gl coordinate system
*/
inline float glCoordSpaceX(int glutCoordX) {
	return (((float)(glutCoordX * 2)) / window->size.x) - 1.;
}
inline float glCoordSpaceY(int glutCoordY) {
	return (((float)(glutCoordY * -2)) / window->size.y) + 1.;
}
inline float glCoordSpaceX(float glutCoordX) {
	return ((glutCoordX * 2) / window->size.x) - 1.;
}
inline float glCoordSpaceY(float glutCoordY) {
	return ((glutCoordY * -2) / window->size.y) + 1.;
}