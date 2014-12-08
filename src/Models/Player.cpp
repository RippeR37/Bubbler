#include "Player.h"
#include "../Game.h"

#include <gl/glew.h>
#include <glfw/glfw3.h>

namespace Model {

    Player::Player() : Bubble() {
        setPosition(glm::vec3(2.5f, 2.5f, -1.0f));
    }

    Player::~Player() {

    }

    void Player::update(double deltaTime) {
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_A) == GLFW_PRESS)
            _position.x -= _speed * static_cast<float>(deltaTime);
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_D) == GLFW_PRESS)
            _position.x += _speed * static_cast<float>(deltaTime);

        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_SPACE) == GLFW_PRESS)
            _position.y += _speed * static_cast<float>(deltaTime);
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            _position.y -= _speed * static_cast<float>(deltaTime);

        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_W) == GLFW_PRESS)
            _position.z += _speed * static_cast<float>(deltaTime);
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_S) == GLFW_PRESS)
            _position.z -= _speed * static_cast<float>(deltaTime);
    }

}