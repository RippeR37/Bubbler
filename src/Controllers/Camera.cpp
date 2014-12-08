#include "Camera.h"

namespace Controller {

    Camera::Camera() : _matrix(glm::mat4(1.0f)) {

    }

    Camera::~Camera() {

    }

    const glm::vec3& Camera::getUp() {
        return _up;
    }

    const glm::vec3& Camera::getRight() {
        return _right;
    }

    const glm::vec3& Camera::getDirection() {
        return _direction;
    }

}