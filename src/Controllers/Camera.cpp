#include "Camera.h"

namespace Controller {

    Camera::Camera() : _matrix(glm::mat4(1.0f)) {

    }

    Camera::~Camera() {

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