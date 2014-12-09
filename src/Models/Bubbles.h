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

            void setMaxCount(unsigned int maxCount);
            
            unsigned int getCount() const;
            unsigned int getMaxCount() const;

            const std::list<Bubble>& getBubbles() const;

        private:
            void createBubble();
            unsigned int addCount() const;

            unsigned int _maxCount;
            std::list<Bubble> _bubbles;
    };

}

#endif