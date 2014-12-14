#include "Bubbles.h"
#include "Aquarium.h"
#include "States.h"

#include <cstdlib>
#include <iostream>

namespace Model {

    Bubbles::Bubbles() {
        resetToLevel(0);

        _baseSpeedFactor = 0.4f;
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

            if(shouldDelete) {
                if(it->isSpecial())
                    setSpecialsCount(getSpecialsCount() - 1);
                it = _bubbles.erase(it);
            } else {
                ++it;
            }
        }

        // Bubble vs bubble collision
        for(auto it = _bubbles.begin(); it != _bubbles.end(); ) {
            auto it2 = it; it2++;
            
            bool destroyFirst = false;
            for(it2; it2 != _bubbles.end(); ) {
                if(it->isCollision(*it2)) {
                    if(it2->isSpecial())
                        setSpecialsCount(getSpecialsCount() - 1);
                    it2 = _bubbles.erase(it2);
                    destroyFirst = true;
                } else {
                    it2++;
                }
            }

            if(destroyFirst) {
                if(it->isSpecial())
                    setSpecialsCount(getSpecialsCount() - 1);

                it = _bubbles.erase(it);
            } else
                it++;
        }
        
        while(addSpecialsCount() > 0)
            createSpecialBubble();

        while(addCount() > 0)
            createBubble();
        
        // Depth-sort
        _bubbles.sort([camPos](Bubble& a, Bubble& b) -> bool {
            return a._distToCam > b._distToCam; 
        });
    }

    void Bubbles::resetToLevel(unsigned int level) {
        setMaxCount(5 + 2 * level);
        setMaxSpecialsCount(5);
        setSpecialsCount(0);

        if(getMaxCount() > 40)
            setMaxCount(40);

        _bubbles.clear();

        _speedFactor = _baseSpeedFactor + static_cast<float>(level) * 0.1f;
    }

    void Bubbles::setMaxCount(unsigned int maxCount) {
        _maxCount = maxCount;
    }
    
    void Bubbles::setSpecialsCount(unsigned int specialsCount) {
        _specialsCount = specialsCount;
    }

    void Bubbles::setMaxSpecialsCount(unsigned int maxSpecialsCount) {
        _maxSpecialsCount = maxSpecialsCount;
    }
            
    unsigned int Bubbles::getCount() const {
        return _bubbles.size();
    }

    unsigned int Bubbles::getMaxCount() const {
        return _maxCount;
    }

    unsigned int Bubbles::getSpecialsCount() const {
        return _specialsCount;
    }

    unsigned int Bubbles::getMaxSpecialsCount() const {
        return _maxSpecialsCount;
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
        speed  = static_cast<float>(rand() % 350) /  350.0f + _speedFactor;

        position.x = static_cast<float>(rand() % 1000) / 200.0f;
        position.y = 0.0f;
        position.z = static_cast<float>(rand() % 1000) / 100.0f;

        color = glm::vec3(static_cast<float>(rand() % 128) / 256.0f + 0.3f);
        color.b += 0.25f;

        bubble.setPosition(position);
        bubble.setColor(color);
        bubble.setRadius(radius);
        bubble.setSpeed(speed);

        _bubbles.push_back(bubble);
    }
    
    void Bubbles::createSpecialBubble() {
        Bubble bubble;
        glm::vec3 position;
        glm::vec3 color;
        float radius;
        float speed;
        
        // randomize data
        radius = static_cast<float>(rand() % 250) / 1000.0f + 0.1f;
        speed  = static_cast<float>(rand() % 350) /  350.0f * 2.0f + _speedFactor;

        position.x = static_cast<float>(rand() % 1000) / 200.0f;
        position.y = 0.0f;
        position.z = static_cast<float>(rand() % 1000) / 100.0f;

        color = glm::vec3(0.7f, 0.3f, 0.3f);

        bubble.setPosition(position);
        bubble.setColor(color);
        bubble.setRadius(radius);
        bubble.setSpeed(speed);
        bubble.setSpecial(true);

        _bubbles.push_back(bubble);

        setSpecialsCount(getSpecialsCount() + 1);
    }

    unsigned int Bubbles::addCount() const {
        return getMaxCount() - getCount();
    }
    
    unsigned int Bubbles::addSpecialsCount() const {
        return getMaxSpecialsCount() - getSpecialsCount();
    }

}