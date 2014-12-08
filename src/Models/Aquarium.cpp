#include "Aquarium.h"

namespace Model {

    Aquarium::Aquarium() {
        setPosition(glm::vec3(0.0f));
        setSize(glm::vec3(5.0f, 5.0f, 10.0f));
        setColor(glm::vec4(0.3f, 0.3, 0.9f, 0.7f));
    }

    Aquarium::~Aquarium() {

    }

    const glm::vec3& Aquarium::getPosition() const {
        return _position;
    }

    const glm::vec3& Aquarium::getSize() const {
        return _size;
    }

    const glm::vec4& Aquarium::getColor() const {
        return _color;
    }

    void Aquarium::setPosition(const glm::vec3& position) {
        _position = position;
    }

    void Aquarium::setSize(const glm::vec3& size) {
        _size = size;
    }

    void Aquarium::setColor(const glm::vec4& color) {
        _color = color;
    }

}