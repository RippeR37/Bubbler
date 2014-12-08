#ifndef VIEW_BUBBLE_H_INCLUDED
#define VIEW_BUBBLE_H_INCLUDED

#include "View.h"
#include "../Utils/GL+/Program.h"
#include "../Utils/GL+/VertexArray.h"
#include "../Utils/GL+/VertexBuffer.h"

#include "../Models/Bubble.h"


namespace View {

    class ViewBubble : public View<Model::Bubble> {
        public:
            ViewBubble();
            ~ViewBubble();
            
            void init(const Model::Bubble& bubble);
            void render(const Model::Bubble& bubble);

        private:
            void initVAO();
            void initVBO(const Model::Bubble& bubble);
            std::vector<glm::vec4> getVertices(const Model::Bubble& bubble);

            unsigned int _drawCount;
            GL::Program _program;
            GL::VertexArray _vao;
            GL::VertexBuffer _vbo;
    };

}

#endif