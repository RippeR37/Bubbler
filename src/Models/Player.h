#ifndef MODEL_PLAYER_H_INCLUDED
#define MODEL_PLAYER_H_INCLUDED

#include "Bubble.h"
#include "Direction.h"

namespace Model {

    class Player : public Bubble {
        public:
            Player();
            ~Player();

            void update(double deltaTime);
            void resetPosition();

        private:
            void checkBoundries();

    };

}

#endif 