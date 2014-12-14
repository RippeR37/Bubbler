#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Controller {

    Camera::Camera() {
        _matrix = glm::mat4(1.0f);
        _projectionMatrix = glm::perspective(glm::radians(90.0f), 4.0f/3.0f, 0.1f, 100.0f);
    }

    Camera::~Camera() {

    }

    const glm::mat4& Camera::getMatrix() const {
        return _matrix;
    }

    const glm::mat4& Camera::getProjection() const {
        return _projectionMatrix;
    }

    const glm::vec3& Camera::getUp() const {
        return _up;
    }

    const glm::vec3& Camera::getRight() const {
        return _right;
    }

    const glm::vec3& Camera::getDirection() const {
        return _direction;
    }

}