#include "Bubbles.h"
#include "Aquarium.h"
#include "States.h"

#include <cstdlib>
#include <iostream>

namespace Model {

    Bubbles::Bubbles() {
        setMaxCount(10);
    }

    Bubbles::~Bubbles() {

    }

    void Bubbles::update(double deltaTime) {
        static Model::Aquarium& aquarium = States::get().gameplay->getAquarium();
        static Model::Player& player = States::get().gameplay->getPlayer();
        static double timeAccumulator = 0.0;
        bool shouldDelete;
        glm::vec3 camPos;
        camPos = States::get().gameplay->getCamera().getPos3D();

        for(auto it = _bubbles.begin(); it != _bubbles.end(); ) {
            shouldDelete = false;
            
            glm::vec3 pos = it->getPosition();
            pos.y = pos.y + it->getSpeed() * static_cast<float>(deltaTime);
            it->setPosition(pos);
            
            float originalRadius = it->_radiusOriginal;
            it->_radius = originalRadius * (1.0f + 0.1f * (it->getPosition().y / static_cast<float>((aquarium.getPosition().y + aquarium.getSize().y))));

            it->_distToCam = glm::distance(camPos, it->getPosition() + glm::vec3(it->getRadius()));

            if(pos.y > aquarium.getPosition().y + aquarium.getSize().y)
                shouldDelete = true;

            if(shouldDelete)
                it = _bubbles.erase(it);
            else
                ++it;
        }

        while(addCount() > 0)
            createBubble();
        
        // Depth-sort
        _bubbles.sort([camPos](Bubble& a, Bubble& b) -> bool {
            return a._distToCam > b._distToCam; 
        });
    }

    void Bubbles::setMaxCount(unsigned int maxCount) {
        _maxCount = maxCount;
    }
            
    unsigned int Bubbles::getCount() const {
        return _bubbles.size();
    }

    unsigned int Bubbles::getMaxCount() const {
        return _maxCount;
    }

    const std::list<Bubble>& Bubbles::getBubbles() const {
        return _bubbles;
    }

    void Bubbles::createBubble() {
        Bubble bubble;
        glm::vec3 position;
        glm::vec3 color;
        float radius;
        float speed;
        
        // randomize data
        radius = static_cast<float>(rand() % 250) / 1000.0f + 0.1f;
        speed  = static_cast<float>(rand() % 500) /  350.0f + 0.2f;

        position.x = static_cast<float>(rand() % 1000) / 200.0f;
        position.y = 0.0f;
        position.z = static_cast<float>(rand() % 1000) / 100.0f;

        color = glm::vec3(static_cast<float>(rand() % 128) / 256.0f + 0.3f);

        bubble.setPosition(position);
        bubble.setColor(color);
        bubble.setRadius(radius);
        bubble.setSpeed(speed);

        _bubbles.push_back(bubble);
    }

    unsigned int Bubbles::addCount() const {
        return getMaxCount() - getCount();
    }

}