#include "MenuScene.hh"

namespace menu {

MenuScene::~MenuScene() {
    for (MenuElement* e : elements) delete e;
    for (Button* b : buttons) delete b;
}

void menuSceneLoop(int value) {

}

void menuSceneDisplayFunc() {

}

void MenuScene::onLoad() {
    menuSceneLoop(counter);
    glutPostRedisplay();
}

void MenuScene::onUnload() {
    counter++;
    for (Button* b : buttons) b->hovered = false;
}

}  // namespace menu