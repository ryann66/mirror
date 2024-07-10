#pragma once

#include <vector>

#include "Scene.hh"
#include "Button.hh"

namespace menu {

const vector::Vector2 DEFAULT_BUTTON_SIZE(160, 40);
const int DEFAULT_BUTTON_SPACING = 20;

void menuSceneDisplayFunc();

/**
 * Scene for menus
 * Written in the fixed function style of openGL
*/
class MenuScene : public Scene {
 public:
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
	friend void menuSceneClickFunc(int, int, int, int);

 private:
	std::vector<MenuElement*> elements;
	std::vector<Button*> buttons;
};

/**
 * Pause menu scene
 * Written in the fixed function style of openGL
*/
class PauseMenuScene : public MenuScene {
 public:
	PauseMenuScene() : MenuScene(PAUSE_MENU) { }
	PauseMenuScene(const PauseMenuScene&) = delete;
	PauseMenuScene& operator=(const PauseMenuScene&) = delete;
	virtual ~PauseMenuScene() = default;
	
	virtual void onLoad();
	virtual void onUnload();
};

/**
 * Creates a new instance of the main menu
*/
Scene* mainMenu();

/**
 * Creates a new instance of the pause menu
*/
Scene* pauseMenu();

}  // namespace menu