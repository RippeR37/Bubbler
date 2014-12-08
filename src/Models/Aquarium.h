#ifndef MODEL_AQUARIUM_H_INCLUDED
#define MODEL_AQUARIUM_H_INCLUDED

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Model {

    class Aquarium {
        public:
            Aquarium();
            ~Aquarium();

            const glm::vec3& getPosition() const;
            const glm::vec3& getSize() const;
            const glm::vec4& getColor() const;

        private:
            void setPosition(const glm::vec3& position);
            void setSize(const glm::vec3& size);
            void setColor(const glm::vec4& color);

            glm::vec3 _position;
            glm::vec3 _size;
            glm::vec4 _color;
    };

}

#endif