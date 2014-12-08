#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "ViewFloor.h"
#include "../Game.h"
#include "../Models/States.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

namespace View {

    ViewFloor::ViewFloor() {
        _program.load(
            GL::Shader("assets/shaders/floor.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/floor.fs", GL::Shader::Type::FragmentShader)
        );
    }

    ViewFloor::~ViewFloor() {

    }

    void ViewFloor::init(const Model::Floor& floor) {
        initVBO(floor);
        initVAO();
    }

    void ViewFloor::render(const Model::Floor& floor) {
        static glm::mat4 matrixMVP;
        
        matrixMVP = Model::States::get().gameplay->getPipeline().getMVP();
        
        _program.use();
        _program["MVP"].setMatrix(matrixMVP);

            _vao.bind();
                glDrawArrays(GL_LINES, 0, _drawCount);
            _vao.unbind();

        _program.unbind();
    }

    void ViewFloor::initVAO() {
        _vao.bind();
            _vbo.bind();
                _vao.enableAttrib(0);
                _vao.setAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
            _vbo.unbind();
        _vao.unbind();
    }

    void ViewFloor::initVBO(const Model::Floor& floor) {
        std::vector<glm::vec4> vertices = getVertices(floor);

        _vbo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
        _vbo.setTarget(GL::VertexBuffer::Target::Array);

        _vbo.bind();
        _vbo.setData(vertices);
        _vbo.unbind();
    }

    std::vector<glm::vec4> ViewFloor::getVertices(const Model::Floor& floor) {
        std::vector<glm::vec4> vertices;

        for(float x = floor.getStartX(); x <= floor.getEndX(); x += floor.getInterval()) {
            vertices.push_back(glm::vec4(x, 0.0f, floor.getStartY(), 1.0f));
            vertices.push_back(glm::vec4(x, 0.0f, floor.getEndY(),   1.0f));
        }

        for(float y = floor.getStartY(); y <= floor.getEndY(); y += floor.getInterval()) {
            vertices.push_back(glm::vec4(floor.getStartX(), 0.0f, y, 1.0f));
            vertices.push_back(glm::vec4(floor.getEndX(),   0.0f, y, 1.0f));
        }
        
        _drawCount = vertices.size();

        return vertices;
    }

}