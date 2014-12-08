#include "Bubble.h"

namespace Model {

    Bubble::Bubble() {
        setSpeed(1.0f);
        setRadius(1.0f);
        setPosition(glm::vec3(0.0f));
        setColor(glm::vec3(0.7f, 0.7f, 0.7f));
    }

    Bubble::~Bubble() {

    }

    void Bubble::setSpeed(float speed) {
        _speed = speed;
    }

    void Bubble::setRadius(float radius) {
        _radius = radius;
    }

    void Bubble::setPosition(const glm::vec3& position) {
        _position = position;
    }

    void Bubble::setColor(const glm::vec3& color) {
        _color = color;
    }

    float Bubble::getSpeed() const {
        return _speed;
    }

    float Bubble::getRadius() const {
        return _radius;
    }

    const glm::vec3& Bubble::getPosition() const {
        return _position;
    }

    const glm::vec3& Bubble::getColor() const {
        return _color;
    }

}