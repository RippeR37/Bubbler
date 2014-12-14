#ifndef MODEL_BUBBLES_H_INCLUDED
#define MODEL_BUBBLES_H_INCLUDED

#include "Bubble.h"

#include <list>

namespace Model {

    class Bubbles {
        public:
            Bubbles();
            ~Bubbles();

            void update(double deltaTime);
            void resetToLevel(unsigned int level);

            void setMaxCount(unsigned int maxCount);
            void setSpecialsCount(unsigned int specialsCount);
            void setMaxSpecialsCount(unsigned int maxSpecialsCount);
            
            unsigned int getCount() const;
            unsigned int getMaxCount() const;
            unsigned int getSpecialsCount() const;
            unsigned int getMaxSpecialsCount() const;

            const std::list<Bubble>& getBubbles() const;

        private:
            void createBubble();
            void createSpecialBubble();

            unsigned int addCount() const;
            unsigned int addSpecialsCount() const;

            unsigned int _maxCount;
            unsigned int _specialsCount;
            unsigned int _maxSpecialsCount;

            float _speedFactor;
            float _baseSpeedFactor;
            std::list<Bubble> _bubbles;
    };

}

#endif