#pragma once

#include <vector>

#include "Scene.hh"
#include "Button.hh"

namespace menu {

void menuSceneDisplayFunc();

/**
 * Scene for menus
 * Written in the fixed function style of openGL
*/
class MenuScene : public Scene {
	MenuScene(SceneType type) : Scene(type, menuSceneDisplayFunc) { }
	MenuScene(const MenuScene&) = delete;
	MenuScene& operator=(const MenuScene&) = delete;
	virtual ~MenuScene();

	void addElement(MenuElement* el) { elements.push_back(el); }
	void addButton(Button* b) { buttons.push_back(b); }

	virtual void onLoad();
	virtual void onUnload();

	friend void hoverFunc(int, int);
	friend void menuSceneDisplayFunc();

 private:
	std::vector<MenuElement*> elements;
	std::vector<Button*> buttons;
};

/**
 * Pause menu scene
 * Written in the fixed function style of openGL
*/
class PauseMenuScene : public MenuScene {
	PauseMenuScene() : MenuScene(PAUSE_MENU) { }
	PauseMenuScene(const PauseMenuScene&) = delete;
	PauseMenuScene& operator=(const PauseMenuScene&) = delete;
	
	virtual void onLoad();
	virtual void onUnload();
};

// TODO function generators for various menus

}  // namespace menu