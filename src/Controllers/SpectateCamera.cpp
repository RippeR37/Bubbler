#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "SpectateCamera.h"
#include "../Game.h"
#include "../Models/States.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Controller {

    SpectateCamera::SpectateCamera() : Camera() {

    }

    SpectateCamera::~SpectateCamera() {

    }
    
    void SpectateCamera::init(const Model::Aquarium& aquarium) {
        _position.x = aquarium.getPosition().x + aquarium.getSize().x + 7.5f;
        _position.y = aquarium.getPosition().y + aquarium.getSize().y + 2.5f;
        _position.z = aquarium.getPosition().z + aquarium.getSize().z * 0.5f;

        _direction.x = aquarium.getPosition().x + aquarium.getSize().x * 0.5f;
        _direction.y = aquarium.getPosition().y + aquarium.getSize().y * 0.5f;
        _direction.z = aquarium.getPosition().z + aquarium.getSize().z * 0.5f;
        _direction = glm::normalize(_direction - _position);

        _right = glm::vec3(0.0f, 0.0f, -1.0f);
        _up = glm::cross(_right, _direction);

        _matrix = glm::lookAt(_position, _position + _direction, _up);
    }

    void SpectateCamera::update(double deltaTime) {
        // This camera doesn't change direction or position

        return;
    }

    void SpectateCamera::updateMouse(double x, double y) {
        // This camera is not affected by mouse

        return;
    }
    
    void SpectateCamera::updateKeyboard(int key, int scancode, int action, int mods) {
        // This camera is not affected by keyboard

        return;
    }

    void SpectateCamera::updateMouseWheel(double x, double y) {
        // This camera is not affected by mouse scrolling

        return;
    }

    const glm::vec2  SpectateCamera::getPos2D() const {
        return glm::vec2(_position[0], _position[2]);
    }

    const glm::vec3& SpectateCamera::getPos3D() const {
        return _position;
    }

    const glm::mat4& SpectateCamera::getMatrix() const {
        return _matrix;
    }

}