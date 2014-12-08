#include "Gameplay.h"
#include "../../Models/States.h"
#include "../../Game.h"
#include "../../Utils/TimeLoop.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace Controller {

    State::Gameplay::Gameplay() : _camera(_lockedCamera) {
        
    }

    void State::Gameplay::update(double frameTime) {
        static const double timeStep = 0.001;

        if(shouldSkip())
            return;

        Util::TimeLoop::semiFixed(frameTime, timeStep, [&, this](double deltaTime) { 
            _camera.update(deltaTime);
            _player.update(deltaTime);
        });

        if(isEnd() == true)
            State::changeTo(Model::States::get().shutdown);
    }

    void State::Gameplay::render() {
        if(shouldSkip())
            return;

        Game::get().getWindow().getContext().clearBuffers(GL::Context::BufferMask::Color);

        _pipeline.getStack().loadID();
        _pipeline.getStack().pushMatrix(_camera.getMatrix());

            _viewFloor.render(_floor);
            _viewAquarium.render(_aquarium);
            _viewBubble.render(_player);

        _pipeline.getStack().popMatrix();
    }

    void State::Gameplay::onLoad() {
        changeTo(this);

        glfwSetCursorPos(Game::get().getWindow().getHandle(), 400.0, 300.0);
        glfwSetKeyCallback(Game::get().getWindow().getHandle(), handleKeyboard);
        glfwSetCursorPosCallback(Game::get().getWindow().getHandle(), handleMouseMovement);

        // Face culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        
        // Blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Game::get().getWindow().getContext().setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

        _viewFloor.init(_floor);
        _viewAquarium.init(_aquarium);
        _viewBubble.init(_player);

        _player.setColor(glm::vec3(0.5f, 0.2f, 0.5f));
        _player.setRadius(0.25f);
    }

    void State::Gameplay::onUnload() {
        glfwSetKeyCallback(Game::get().getWindow().getHandle(), nullptr);
    }
    
    Camera& State::Gameplay::getCamera() {
        return _camera;
    }

    LockedCamera& State::Gameplay::getLockedCamera() {
        return _lockedCamera;
    }

    Model::Aquarium& State::Gameplay::getAquarium() {
        return _aquarium;
    }
    
    Model::Player& State::Gameplay::getPlayer() {
        return _player;
    }

    GL::Pipeline& State::Gameplay::getPipeline() {
        return _pipeline;
    }

    void State::Gameplay::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
        static State::Gameplay& thisState = *Model::States::get().gameplay;

        if(action == GLFW_PRESS) {
            switch(key) {
                case GLFW_KEY_ESCAPE:
                    thisState.changeTo(Model::States::get().shutdown);
                    break;

                default:
                    break;
            }

        } else if(action == GLFW_RELEASE) {
            
        }

        thisState.getCamera().updateKeyboard(key, scancode, action, mods);
    }
    
    void State::Gameplay::handleMouseMovement(GLFWwindow* window, double x, double y) {
        static double centerX = 400.0;
        static double centerY = 300.0;
        static double dx = -1.0;
        static double dy;

        dx = x - centerX;
        dy = y - centerY;

        Model::States::get().gameplay->getCamera().updateMouse(static_cast<int>(dx), static_cast<int>(dy));

        glfwSetCursorPos(window, centerX, centerY);
    }
    
    void State::Gameplay::setCamera(Camera& camera) {
        _camera = camera;
    }

    bool State::Gameplay::isEnd() const {
        return false;
    };

}
