#pragma once

#include <string>

#include "Window.hh"
#include "MenuScene.hh"

namespace menu {

/**
 * Scene to be rendered to show an error
 */
class ErrorScene : public MenuScene {
 public:
	ErrorScene(std::string& errorMessage);
	ErrorScene(const ErrorScene&) = delete;
	ErrorScene& operator=(const ErrorScene&) = delete;
	virtual ~ErrorScene() { }
};

/**
 * Function for quickly creating and displaying an error scene
 */
void newErrorScene(std::string errorMessage);

}  // namespace menu