#include "ErrorScene.hh"

#include "Vector2.hh"
#include "Label.hh"
#include "Button.hh"

namespace menu {

/**
 * Function callback for returning to the main menu
 */
void mainMenuFunc() {
	window->replaceScene(MAIN_MENU);
}

ErrorScene::ErrorScene(std::string& errorMessage) : MenuScene(ERROR_SCENE) {
	this->addButton(new EasyButton(CENTER, vector::Vector2(0, DEFAULT_BUTTON_SIZE.y / 2), DEFAULT_BUTTON_SIZE, "Main Menu", mainMenuFunc));
	this->addElement(new Label(CENTER, vector::Vector2(0, -DEFAULT_BUTTON_SIZE.y / 2), errorMessage, MenuLabelColor));
}

void newErrorScene(std::string errorMessage) {
	Scene* ms = new ErrorScene(errorMessage);
	window->addScene(ms);
	window->loadScene(ERROR_SCENE);
}

}  // namespace menu