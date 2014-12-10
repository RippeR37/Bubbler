#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "ViewAquarium.h"
#include "../Game.h"
#include "../Models/States.h"

#include <iostream>
#include <vector>

namespace View {

    ViewAquarium::ViewAquarium() {
        _program.load(
            GL::Shader("assets/shaders/aquarium.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/aquarium.fs", GL::Shader::Type::FragmentShader)
        );
    }

    ViewAquarium::~ViewAquarium() {

    }

    void ViewAquarium::init(const Model::Aquarium& aquarium) {
        initVBO(aquarium);
        initVAO();
    }

    void ViewAquarium::render(const Model::Aquarium& aquarium) {
        static Controller::State::Gameplay& gameplay = *Model::States::get().gameplay;
        static glm::vec4 color = gameplay.getAquarium().getColor();
        static glm::vec3 camPos;
        static glm::mat4 matrixMVP;

        matrixMVP = gameplay.getPipeline().getMVP();
        camPos = gameplay.getPlayer().getPosition();

        glm::vec3 lightbubblePosition[5];
        int count = 0;
        for(auto it = gameplay.getBubbles().getBubbles().begin(); it != gameplay.getBubbles().getBubbles().end(); ++it) {
            if(it->isSpecial()) {
                lightbubblePosition[count] = it->getPosition();
                ++count;
            }

            if(count == 5) 
                break;
        }
        
        _program.use();
        _program["MVP"].setMatrix(matrixMVP);
        _program["CamPos"].setVec(camPos);
        _program["uColor"].setVec(color);
        _program["lightbubblePosition"].setVec(lightbubblePosition[0], count);

            _vao.bind();
                glDrawArrays(GL_TRIANGLES, 0, _drawCount);
            _vao.unbind();

        _program.unbind();
    }

    void ViewAquarium::initVAO() {
        _vao.bind();
            _vbo.bind();
                _vao.enableAttrib(0);
                _vao.setAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
            _vbo.unbind();
        _vao.unbind();
    }

    void ViewAquarium::initVBO(const Model::Aquarium& aquarium) {
        std::vector<glm::vec4> vertices = getVertices(aquarium);

        _vbo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
        _vbo.setTarget(GL::VertexBuffer::Target::Array);

        _vbo.bind();
        _vbo.setData(vertices);
        _vbo.unbind();
    }

    std::vector<glm::vec4> ViewAquarium::getVertices(const Model::Aquarium& aquarium) {
        std::vector<glm::vec4> vertices;
        float x, y, z;
        float w, h, d;

        x = aquarium.getPosition().x;
        y = aquarium.getPosition().y;
        z = aquarium.getPosition().z;

        w = aquarium.getSize().x;
        h = aquarium.getSize().y;
        d = aquarium.getSize().z;

        // Bottom
        vertices.push_back(glm::vec4(x,     y, z,     1.0f));
        vertices.push_back(glm::vec4(x,     y, z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y, z,     1.0f));
        vertices.push_back(glm::vec4(x + w, y, z,     1.0f));
        vertices.push_back(glm::vec4(x,     y, z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y, z + d, 1.0f));

        // Up
        vertices.push_back(glm::vec4(x,     y + h, z,     1.0f));
        vertices.push_back(glm::vec4(x + w, y + h, z,     1.0f));
        vertices.push_back(glm::vec4(x,     y + h, z + d, 1.0f));
        vertices.push_back(glm::vec4(x,     y + h, z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y + h, z,     1.0f));
        vertices.push_back(glm::vec4(x + w, y + h, z + d, 1.0f));

        // Left
        vertices.push_back(glm::vec4(x, y,     z,     1.0f));
        vertices.push_back(glm::vec4(x, y + h, z,     1.0f));
        vertices.push_back(glm::vec4(x, y,     z + d, 1.0f));
        vertices.push_back(glm::vec4(x, y,     z + d, 1.0f));
        vertices.push_back(glm::vec4(x, y + h, z,     1.0f));
        vertices.push_back(glm::vec4(x, y + h, z + d, 1.0f));
        
        // Right
        vertices.push_back(glm::vec4(x + w, y,     z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y + h, z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y,     z,     1.0f));
        vertices.push_back(glm::vec4(x + w, y,     z,     1.0f));
        vertices.push_back(glm::vec4(x + w, y + h, z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y + h, z,     1.0f));
        
        // Front
        vertices.push_back(glm::vec4(x,     y,     z, 1.0f));
        vertices.push_back(glm::vec4(x + w, y,     z, 1.0f));
        vertices.push_back(glm::vec4(x,     y + h, z, 1.0f));
        vertices.push_back(glm::vec4(x,     y + h, z, 1.0f));
        vertices.push_back(glm::vec4(x + w, y,     z, 1.0f));
        vertices.push_back(glm::vec4(x + w, y + h, z, 1.0f));
        
        // Back
        vertices.push_back(glm::vec4(x,     y,     z + d, 1.0f));
        vertices.push_back(glm::vec4(x,     y + h, z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y,     z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y,     z + d, 1.0f));
        vertices.push_back(glm::vec4(x,     y + h, z + d, 1.0f));
        vertices.push_back(glm::vec4(x + w, y + h, z + d, 1.0f));
        
        _drawCount = vertices.size();

        return vertices;
    }

}