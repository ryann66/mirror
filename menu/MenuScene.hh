#pragma once

#include <vector>

#include "Scene.hh"
#include "Button.hh"

namespace menu {

void menuSceneDisplayFunc();

/**
 * Scene for menus
 * Written in the fixed function style of openGL 2
*/
class MenuScene : public Scene {
    MenuScene(SceneType type) : Scene(type, menuSceneDisplayFunc) { }
    MenuScene(const MenuScene&) = delete;
    MenuScene& operator=(const MenuScene&) = delete;
    virtual ~MenuScene();

    void addElement(MenuElement* el) { elements.push_back(el); }
    void addButton(Button* b) { buttons.push_back(b); }

    virtual void onLoad() = 0;
	virtual void onUnload() = 0;

 private:
    std::vector<MenuElement*> elements;
    std::vector<Button*> buttons;
    
    // counter for ensuring display function terminates on unload
    mutable int counter = 0;
};

}  // namespace menu