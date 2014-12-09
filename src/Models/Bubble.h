#ifndef MODEL_BUBBLE_H_INCLUDED
#define MODEL_BUBBLE_H_INCLUDED

#include <glm/vec3.hpp>

namespace Model {

    class Bubble {
        public:
            Bubble();
            virtual ~Bubble();

            void setSpeed(float speed);
            void setRadius(float radius);
            void setPosition(const glm::vec3& position);
            void setColor(const glm::vec3& color);
            
            bool isCollision(const Bubble& bubble) const;
            float getSpeed() const;
            float getRadius() const;
            float getDistToCam() const;
            const glm::vec3& getPosition() const;
            const glm::vec3& getColor() const;

        protected:
            float _speed;
            float _radius;
            float _radiusOriginal;

            glm::vec3 _position;
            glm::vec3 _color;

        private:
            float _distToCam;
            
        public:
            friend class Bubbles;
    };
    
}

#endif