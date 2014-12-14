#include "TestView.h"
#include "../Models/States.h"

#include <iostream>

namespace View {

    TestView::TestView() {
        _program.load(
            GL::Shader("assets/shaders/test.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/test.fs", GL::Shader::Type::FragmentShader)
        );
    }

    TestView::~TestView() {

    }
            
    void TestView::render() {
        static Controller::State::Gameplay& gameplay = *Model::States::get().gameplay;

        gameplay.getPipeline().getStack().pushMatrix();

            gameplay.getPipeline().getStack().translate(glm::vec3(3.0f));
            _program.use();
            _program["MVP"].setMatrix(gameplay.getPipeline().getMVP());
                

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                _vao.bind();
                _vao.drawArrays();
                _vao.unbind();
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            _program.unbind();

        gameplay.getPipeline().getStack().popMatrix();
    }

    void TestView::setVertexData() {

        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec4> vertices;

        {
            float alpha[2];
            float betta[2];
            float PI = 3.14f;
            int xPaths = 20;
            int yPaths = 20;


            for(int x = 0; x < xPaths; ++x) {
                alpha[0] = ((float)(x)   / (float)(xPaths)) * PI * 2.0f;
                alpha[1] = ((float)(x+1) / (float)(xPaths)) * PI * 2.0f;
                
                for(int y = 0; y < yPaths; ++y) {
                    betta[0] = ((float)(y)   / (float)(yPaths)) * PI * 2.0f;
                    betta[1] = ((float)(y+1) / (float)(yPaths)) * PI * 2.0f;

                    vertices.push_back(glm::vec4(std::cos(alpha[0]) * std::cos(betta[0]), std::cos(alpha[0]) * std::sin(betta[0]), std::sin(alpha[0]), 1.0f));
                    vertices.push_back(glm::vec4(std::cos(alpha[1]) * std::cos(betta[0]), std::cos(alpha[1]) * std::sin(betta[0]), std::sin(alpha[1]), 1.0f));
                    vertices.push_back(glm::vec4(std::cos(alpha[0]) * std::cos(betta[1]), std::cos(alpha[0]) * std::sin(betta[1]), std::sin(alpha[0]), 1.0f));
                    
                    vertices.push_back(glm::vec4(std::cos(alpha[0]) * std::cos(betta[1]), std::cos(alpha[0]) * std::sin(betta[1]), std::sin(alpha[0]), 1.0f));
                    vertices.push_back(glm::vec4(std::cos(alpha[1]) * std::cos(betta[0]), std::cos(alpha[1]) * std::sin(betta[0]), std::sin(alpha[1]), 1.0f));
                    vertices.push_back(glm::vec4(std::cos(alpha[1]) * std::cos(betta[1]), std::cos(alpha[1]) * std::sin(betta[1]), std::sin(alpha[1]), 1.0f));
                }
            }
        }
        
        // VertexData assignment
        vertexData.data = &vertices[0];
        vertexData.size = vertices.size() * sizeof(glm::vec4);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, 0));

        // Set VBO
        _vbo.setData(vertexData);

        // Set VAO
        _vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);
        _vao.setDrawOffset(0);
        _vao.setDrawCount(vertices.size());
    }


}