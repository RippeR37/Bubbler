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
            void resetFinishedLevel();

            bool isAlive() const;
            bool isFinishedLevel() const;

        private:
            void checkBoundries();
            void checkCollision();

            bool _isAlive;
            bool _isFinishedLevel;
    };

}

#endif 