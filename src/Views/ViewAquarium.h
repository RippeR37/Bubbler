#ifndef VIEW_AQUARIUM_H_INCLUDED
#define VIEW_AQUARIUM_H_INCLUDED

#include "View.h"
#include "../Utils/GL+/Program.h"
#include "../Utils/GL+/VertexArray.h"
#include "../Utils/GL+/VertexBuffer.h"

#include "../Models/Aquarium.h"

#include <glm/vec4.hpp>

namespace View {

    class ViewAquarium : public View<Model::Aquarium> {
        public:
            ViewAquarium();
            ~ViewAquarium();
            
            void init(const Model::Aquarium& aquarium);
            void render(const Model::Aquarium& aquarium);

        private:
            void initVAO();
            void initVBO(const Model::Aquarium& aquarium);
            std::vector<glm::vec4> getVertices(const Model::Aquarium& aquarium);

            unsigned int _drawCount;
            GL::Program _program;
            GL::VertexArray _vao;
            GL::VertexBuffer _vbo;
    };

}

#endif