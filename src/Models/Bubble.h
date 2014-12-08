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

            float getSpeed() const;
            float getRadius() const;
            const glm::vec3& getPosition() const;
            const glm::vec3& getColor() const;

        protected:
            float _speed;
            float _radius;
            glm::vec3 _position;
            glm::vec3 _color;
            
    };
    
}

#endif