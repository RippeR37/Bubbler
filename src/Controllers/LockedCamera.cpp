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

        _angleX = 3.14159265f;  // 45 deg
        _angleY = 0.17453292f;  // 10 deg

        _speed = 1.0f;
        _mouseSpeed = 0.003f;
    }

    LockedCamera::~LockedCamera() {

    }

    void LockedCamera::update(double deltaTime) {
        float distToBubble = 3.0f;
        glm::vec3 bubblePos = Model::States::get().gameplay->getPlayer().getPosition();

        bubblePos.z = -bubblePos.z;
        _direction = glm::vec3(std::cos(_angleY) * std::sin(_angleX), std::sin(_angleY), std::cos(_angleY) * cos(_angleX));
        _right     = glm::vec3(std::sin(_angleX - 3.14f/2.0f), 0, std::cos(_angleX - 3.14f/2.0f));
        _up        = glm::cross(_right, _direction);
        _position = bubblePos - _direction * distToBubble;

        _matrix = glm::lookAt(_position, bubblePos, _up);
    }

    void LockedCamera::updateMouse(double x, double y) {
        _angleX -= static_cast<float>(x) * _mouseSpeed;
        _angleY -= static_cast<float>(y) * _mouseSpeed;

        if(_angleX < 2.09439510239f)
            _angleX = 2.09439510239f;
        else if(_angleX > 4.18879020479f)
            _angleX = 4.18879020479f;

        if(_angleY < - 1.3f)
            _angleY = -1.3f;
        else if(_angleY > 1.3f)
            _angleY = 1.3f;
    }
    
    void LockedCamera::updateKeyboard(int key, int scancode, int action, int mods) {
        // This camera is not affected by keyboard

        return;
    }

    const glm::vec2  LockedCamera::getPos2D() {
        return glm::vec2(_position[0], _position[2]);
    }

    const glm::vec3& LockedCamera::getPos3D() {
        return _position;
    }

    const glm::mat4& LockedCamera::getMatrix() {
        return _matrix;
    }

}