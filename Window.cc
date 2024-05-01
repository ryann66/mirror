#include <stdexcept>

#include "Window.hh"

using std::logic_error;

Window::Window(Scene* mainScene) {
    activeScene = mainScene->getType();
    scenes[activeScene] = mainScene;
    mainScene->onLoad();
}

Window::~Window() {
    scenes[activeScene]->onUnload();
    for (auto scp : scenes) delete scp.second;
}

void Window::loadScene(SceneType scene) {
    Scene* ns = scenes[scene];
    if (ns == nullptr) throw new logic_error("Attempted to load nonexistent scene");
    scenes[activeScene]->onUnload();
    activeScene = scene;
    ns->onLoad();
}

void Window::addScene(Scene* scene) {
    SceneType type = scene->getType();
    Scene* ex = scenes[type];
    if (ex != nullptr) {
        if (ex->destroyable()) {
            delete ex;
        } else {
            throw new logic_error("Duplicates of scene type");
        }
    }
    scenes[type] = scene;
}