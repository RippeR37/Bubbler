#ifndef VIEW_FLOOR_H_INCLUDED
#define VIEW_FLOOR_H_INCLUDED

#include "View.h"
#include "../Utils/GL+/Program.h"
#include "../Utils/GL+/VertexArray.h"
#include "../Utils/GL+/VertexBuffer.h"

#include "../Models/Floor.h"

#include <glm/vec4.hpp>

namespace View {

    class ViewFloor : public View<Model::Floor> {
        public:
            ViewFloor();
            ~ViewFloor();
            
            void init(const Model::Floor& floor);
            void render(const Model::Floor& floor);

        private:
            void initVAO();
            void initVBO(const Model::Floor& floor);
            std::vector<glm::vec4> getVertices(const Model::Floor& floor);

            unsigned int _drawCount;
            GL::Program _program;
            GL::VertexArray _vao;
            GL::VertexBuffer _vbo;
    };

}

#endif