#include "Gameplay.h"
#include "../../Models/States.h"
#include "../../Game.h"
#include "../../Utils/TimeLoop.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace Controller {

    State::Gameplay::Gameplay() : _camera(_lockedCamera) {
        _cameraType = Model::CameraType::Locked;
    }

    void State::Gameplay::update(double frameTime) {
        static const double timeStep = 0.001;

        if(shouldSkip())
            return;
        
        Util::TimeLoop::semiFixed(frameTime, timeStep, [&, this](double deltaTime) { 
            if(_cameraType == Model::CameraType::Locked)
                _lockedCamera.update(deltaTime);
            
            _player.update(deltaTime);
            _bubbles.update(deltaTime);
        });

        if(isEnd() == true)
            State::changeTo(Model::States::get().shutdown);
    }

    void State::Gameplay::render() {
        if(shouldSkip())
            return;
        
        bool playerRendered = false;
        Game::get().getWindow().getContext().clearBuffers(GL::Context::BufferMask::Color_Depth);
        
        _pipeline.getStack().pushMatrix(_camera.getMatrix());
            
            _viewFloor.render(_floor);
            _viewAquarium.render(_aquarium);
            
            glEnable(GL_DEPTH_TEST);
                for(auto it = _bubbles.getBubbles().begin() ; it != _bubbles.getBubbles().end(); ++it) {
                    if(playerRendered == false && it->getDistToCam() < 3.5f) {
                        _viewBubble.render(_player);
                        playerRendered = true;
                    }
                    _viewBubble.render(*it);
                }

                if(playerRendered == false)
                    _viewBubble.render(_player);
            glDisable(GL_DEPTH_TEST);

        _pipeline.getStack().popMatrix();
    }

    void State::Gameplay::onLoad() {
        changeTo(this);

        glfwSetCursorPos(Game::get().getWindow().getHandle(), 400.0, 300.0);

        glfwSetKeyCallback(Game::get().getWindow().getHandle(), handleKeyboard);
        glfwSetScrollCallback(Game::get().getWindow().getHandle(), handleMouseScrolling);
        glfwSetCursorPosCallback(Game::get().getWindow().getHandle(), handleMouseMovement);

        // Depth testing
        glDepthFunc(GL_LESS);

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

        _spectateCamera.init(_aquarium);
    }

    void State::Gameplay::onUnload() {
        glfwSetKeyCallback(Game::get().getWindow().getHandle(),         nullptr);
        glfwSetScrollCallback(Game::get().getWindow().getHandle(),      nullptr);
        glfwSetCursorPosCallback(Game::get().getWindow().getHandle(),   nullptr);
    }
    
    Camera& State::Gameplay::getCamera() {
        return _camera;
    }

    LockedCamera& State::Gameplay::getLockedCamera() {
        return _lockedCamera;
    }

    SpectateCamera& State::Gameplay::getSpectateCamera() {
        return _spectateCamera;
    }

    Model::Aquarium& State::Gameplay::getAquarium() {
        return _aquarium;
    }
    
    Model::Player& State::Gameplay::getPlayer() {
        return _player;
    }
    
    Model::Bubbles& State::Gameplay::getBubbles() {
        return _bubbles;
    }

    GL::Pipeline& State::Gameplay::getPipeline() {
        return _pipeline;
    }

    Model::CameraType State::Gameplay::getCameraType() const {
        return _cameraType;
    }

    void State::Gameplay::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
        static State::Gameplay& thisState = *Model::States::get().gameplay;

        if(action == GLFW_PRESS) {
            switch(key) {
                case GLFW_KEY_ESCAPE:
                    thisState.changeTo(Model::States::get().shutdown);
                    break;

                case GLFW_KEY_TAB:
                    switch(Model::States::get().gameplay->_cameraType) {
                        case Model::CameraType::Locked: 
                            Model::States::get().gameplay->setCamera(Model::CameraType::Spectate);
                            break;
                        case Model::CameraType::Spectate: 
                            Model::States::get().gameplay->setCamera(Model::CameraType::Locked);
                            break;
                    }
                    break;

                
                default:
                    break;
            }

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
    
    void State::Gameplay::handleMouseScrolling(GLFWwindow* window, double x, double y) {
        Controller::State::Gameplay& thisState = *Model::States::get().gameplay;

        if(thisState._cameraType == Model::CameraType::Locked)
            Model::States::get().gameplay->getLockedCamera().updateMouseWheel(x, y);
    }
    
    void State::Gameplay::setCamera(Model::CameraType cameraType) {
        _cameraType = cameraType;

        switch(cameraType) {
            case Model::CameraType::Locked: 
                _camera = getLockedCamera();
                getLockedCamera().resetProjection();
                _pipeline.setProjection(getLockedCamera().getProjection());
                break;

            case Model::CameraType::Spectate: 
                _camera = getSpectateCamera();
                _pipeline.setProjection(getSpectateCamera().getProjection());
                break;
        }
    }

    bool State::Gameplay::isEnd() const {
        return false;
    };

}
