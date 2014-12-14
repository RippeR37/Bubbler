#include "Loss.h"
#include "../../Game.h"
#include "../../Models/States.h"

namespace Controller {

    State::Loss::Loss() {

    }

    void State::Loss::update(const double frameTime) {
        // Do nothing, wait to quit
    }

    void State::Loss::render() {
        // Render Gameplay's state (last frame)
        Model::States::get().gameplay->render();
    }

    void State::Loss::onLoad() {
        glfwSetKeyCallback(Game::get().getWindow().getHandle(), handleKeyboard);
    }

    void State::Loss::onUnload() {
        glfwSetKeyCallback(Game::get().getWindow().getHandle(), nullptr);
    }

    void State::Loss::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {

    }

}