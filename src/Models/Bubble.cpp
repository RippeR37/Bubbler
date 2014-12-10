#include "Bubble.h"

#include <glm/geometric.hpp>

namespace Model {

    Bubble::Bubble() {
        setSpeed(1.0f);
        setRadius(1.0f);
        setPosition(glm::vec3(0.0f));
        setColor(glm::vec3(0.7f, 0.7f, 0.7f));
        setSpecial(false);
    }

    Bubble::~Bubble() {

    }

    void Bubble::setSpecial(bool flag) {
        _isSpecial = flag;
    }

    void Bubble::setSpeed(float speed) {
        _speed = speed;
    }

    void Bubble::setRadius(float radius) {
        _radius = radius;
        _radiusOriginal = radius;
    }

    void Bubble::setPosition(const glm::vec3& position) {
        _position = position;
    }

    void Bubble::setColor(const glm::vec3& color) {
        _color = color;
    }
    
    bool Bubble::isSpecial() const {
        return _isSpecial;
    }

    bool Bubble::isCollision(const Bubble& bubble) const {
        float r1 = getRadius();
        float r2 = bubble.getRadius();

        float distance = glm::distance(
            getPosition() + glm::vec3(r1, r1, -r1), 
            bubble.getPosition() + glm::vec3(r2, r2, -r2)
        );

        return distance < r1 + r2;
    }


    float Bubble::getSpeed() const {
        return _speed;
    }

    float Bubble::getRadius() const {
        return _radius;
    }
    
    float Bubble::getDistToCam() const {
        return _distToCam;
    }

    const glm::vec3& Bubble::getPosition() const {
        return _position;
    }

    const glm::vec3& Bubble::getColor() const {
        return _color;
    }

}