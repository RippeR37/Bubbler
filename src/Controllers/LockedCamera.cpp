#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "LockedCamera.h"
#include "../Game.h"
#include "../Models/States.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace Controller {

    LockedCamera::LockedCamera() : Camera() {
        _position = glm::vec3(0.0f, 1.0f, 0.0f);

        _speed = 1.0f;
        _mouseSpeed = 0.003f;
        _fovAngle = 90.0f;

        resetAngles();
    }

    LockedCamera::~LockedCamera() {

    }

    void LockedCamera::update(double deltaTime) {
        float distToBubble = 3.0f;
        glm::vec3 bubblePos = Model::States::get().gameplay->getPlayer().getPosition();

        _direction = glm::vec3(std::cos(_angleY) * std::sin(_angleX), std::sin(_angleY), std::cos(_angleY) * cos(_angleX));
        _right     = glm::vec3(std::sin(_angleX - 3.14f/2.0f), 0, std::cos(_angleX - 3.14f/2.0f));
        _up        = glm::cross(_right, _direction);
        _position = bubblePos - _direction * distToBubble;

        _matrix = glm::lookAt(_position, bubblePos, _up);
    }

    void LockedCamera::updateMouse(double x, double y) {
        _angleX -= static_cast<float>(x) * _mouseSpeed;
        _angleY -= static_cast<float>(y) * _mouseSpeed;

        if(_angleY < - 1.3f)
            _angleY = -1.3f;
        else if(_angleY > 1.3f)
            _angleY = 1.3f;
    }
    
    void LockedCamera::updateKeyboard(int key, int scancode, int action, int mods) {
        // This camera is not affected by keyboard

        return;
    }

    void LockedCamera::updateMouseWheel(double x, double y) {
        _fovAngle += static_cast<float>(y) * 2.0f;

        if(_fovAngle < 31.0f)
            _fovAngle = 31.0f;

        else if(_fovAngle > 121.0f)
            _fovAngle = 121.0f;

        resetProjection();
    }

    void LockedCamera::resetProjection() {
        _projectionMatrix = glm::perspective(glm::radians(_fovAngle), 4.0f/3.0f, 0.1f, 100.0f);

        Model::States::get().gameplay->getPipeline().setProjection(_projectionMatrix);
    }
    
    void LockedCamera::resetAngles() {
        _angleX = 0;
        _angleY = 0;
    }

    float LockedCamera::getAngleX() const {
        return _angleX;
    }

    float LockedCamera::getAngleY() const {
        return _angleY;
    }

    const glm::vec2  LockedCamera::getPos2D() const {
        return glm::vec2(_position[0], _position[2]);
    }

    const glm::vec3& LockedCamera::getPos3D() const {
        return _position;
    }

    const glm::mat4& LockedCamera::getMatrix() const {
        return _matrix;
    }

}