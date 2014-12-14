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

    void ViewFloor::render(const Model::Floor& floor) {
        _program.use();
        _program["MVP"].setMatrix(Model::States::get().gameplay->getPipeline().getMVP());

            _vao.bind();
            _vao.drawArrays();
            _vao.unbind();

        _program.unbind();
    }

    void ViewFloor::setVertexData(const Model::Floor& floor) {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec4> vertices;

        {
            for(float x = floor.getStartX(); x <= floor.getEndX(); x += floor.getInterval()) {
                vertices.push_back(glm::vec4(x, 0.0f, floor.getStartY(), 1.0f));
                vertices.push_back(glm::vec4(x, 0.0f, floor.getEndY(),   1.0f));
            }

            for(float y = floor.getStartY(); y <= floor.getEndY(); y += floor.getInterval()) {
                vertices.push_back(glm::vec4(floor.getStartX(), 0.0f, y, 1.0f));
                vertices.push_back(glm::vec4(floor.getEndX(),   0.0f, y, 1.0f));
            }

            vertices.push_back(glm::vec4(floor.getStartX(), floor.getEndX() - floor.getStartX(), floor.getEndY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getEndX(),   floor.getEndX() - floor.getStartX(), floor.getEndY(), 1.0f));

            vertices.push_back(glm::vec4(floor.getStartX(), floor.getEndX() - floor.getStartX(), floor.getStartY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getStartX(), floor.getEndX() - floor.getStartX(), floor.getEndY(),   1.0f));
        
            vertices.push_back(glm::vec4(floor.getEndX(),   floor.getEndX() - floor.getStartX(), floor.getStartY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getEndX(),   floor.getEndX() - floor.getStartX(), floor.getEndY(),   1.0f));
            
            /*
            vertices.push_back(glm::vec4(floor.getStartX(), floor.getEndX() - floor.getStartX(), floor.getStartY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getEndX(),   floor.getEndX() - floor.getStartX(), floor.getStartY(), 1.0f));

            vertices.push_back(glm::vec4(floor.getStartX(), 0.0f,                                floor.getStartY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getStartX(), floor.getEndX() - floor.getStartX(), floor.getStartY(), 1.0f));

            vertices.push_back(glm::vec4(floor.getEndX(),   0.0f,                                floor.getStartY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getEndX(),   floor.getEndX() - floor.getStartX(), floor.getStartY(), 1.0f));
            */

            vertices.push_back(glm::vec4(floor.getStartX(), 0.0f,                                floor.getEndY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getStartX(), floor.getEndX() - floor.getStartX(), floor.getEndY(), 1.0f));

            vertices.push_back(glm::vec4(floor.getEndX(),   0.0f,                                floor.getEndY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getEndX(),   floor.getEndX() - floor.getStartX(), floor.getEndY(), 1.0f));
        
            vertices.push_back(glm::vec4(floor.getStartX(), 0.0f,                                floor.getEndY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getEndX(),   floor.getEndX() - floor.getStartX(), floor.getEndY(), 1.0f));

            vertices.push_back(glm::vec4(floor.getStartX(), floor.getEndX() - floor.getStartX(), floor.getEndY(), 1.0f));
            vertices.push_back(glm::vec4(floor.getEndX(),   0.0f,                                floor.getEndY(), 1.0f));
        }

        // VertexData assignment
        vertexData.data = &vertices[0];
        vertexData.size = vertices.size() * sizeof(glm::vec4);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, 0));

        // Set VBO
        _vbo.setData(vertexData);

        // Set VAO
        _vao.setDrawTarget(GL::VertexArray::DrawTarget::Lines);
        _vao.setDrawCount(vertices.size());
        _vao.attachVBO(&_vbo);
    }

}