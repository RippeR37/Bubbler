#include "Player.h"
#include "../Game.h"
#include "../Models/States.h"

#include <gl/glew.h>
#include <glfw/glfw3.h>

namespace Model {

    Player::Player() : Bubble() {
        setPosition(glm::vec3(2.5f, 2.5f, -1.0f));
    }

    Player::~Player() {

    }

    void Player::update(double deltaTime) {
        bool axisAligned = false;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 front;

        if(axisAligned) {
            up    = glm::vec3(0.0f, 1.0f, 0.0f);
            right = glm::vec3(1.0f, 0.0f, 0.0f);
            front = glm::vec3(0.0f, 0.0f, 1.0f);
        } else {
            up    = Model::States::get().gameplay->getCamera().getUp();             up.z = -up.z;
            right = Model::States::get().gameplay->getCamera().getRight();          right.z = -right.z;
            front = Model::States::get().gameplay->getCamera().getDirection();      front.z = -front.z;
        }

        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_A) == GLFW_PRESS)
            //_position.x -= _speed * static_cast<float>(deltaTime);
            _position -= _speed * static_cast<float>(deltaTime) * right;
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_D) == GLFW_PRESS)
            //_position.x += _speed * static_cast<float>(deltaTime);
            _position += _speed * static_cast<float>(deltaTime) * right;

        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_SPACE) == GLFW_PRESS)
            //_position.y += _speed * static_cast<float>(deltaTime);
            _position += _speed * static_cast<float>(deltaTime) * up;
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            //_position.y -= _speed * static_cast<float>(deltaTime);
            _position -= _speed * static_cast<float>(deltaTime) * up;

        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_W) == GLFW_PRESS)
            //_position.z += _speed * static_cast<float>(deltaTime);
            _position += _speed * static_cast<float>(deltaTime) * front;
        if(glfwGetKey(Game::get().getWindow().getHandle(), GLFW_KEY_S) == GLFW_PRESS)
            //_position.z -= _speed * static_cast<float>(deltaTime);
            _position -= _speed * static_cast<float>(deltaTime) * front;
    }

}