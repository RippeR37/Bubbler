#include "ViewAquarium.h"
#include "ViewBubble.h"
#include "../Game.h"
#include "../Models/States.h"

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

    void ViewAquarium::render(const Model::Aquarium& aquarium) {
        static Controller::State::Gameplay& gameplay = *Model::States::get().gameplay;
        static glm::vec4 color;
        static glm::vec3 camPos;
        static glm::mat4 matrixMVP;
        static glm::vec3 lightbubblePosition[5];
        static int lightbubbleCount;

        color     = gameplay.getAquarium().getColor();
        camPos    = gameplay.getPlayer().getPosition();
        matrixMVP = gameplay.getPipeline().getMVP();
        lightbubbleCount = ViewBubble::assignLigtbubblePositions(lightbubblePosition, 5);

        _program.use();
            _program["MVP"].setMatrix(matrixMVP);
            _program["CamPos"].setVec(camPos);
            _program["uColor"].setVec(color);
            _program["lightbubblePosition"].setVec(lightbubblePosition[0], lightbubbleCount);
            _program["lightbubbleCount"].set(lightbubbleCount);

            _vao.bind();
            _vao.drawArrays();
            _vao.unbind();

        _program.unbind();
    }

    void ViewAquarium::setVertexData(const Model::Aquarium& aquarium) {
        GL::VertexBuffer::Data vertexData;
        std::vector<glm::vec4> vertices;

        {
            float x, y, z;
            float w, h, d;

            x = aquarium.getPosition().x;       w = aquarium.getSize().x;
            y = aquarium.getPosition().y;       h = aquarium.getSize().y;
            z = aquarium.getPosition().z;       d = aquarium.getSize().z;

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
        }
        
        // VertexData assignment
        vertexData.data = &vertices[0];
        vertexData.size = vertices.size() * sizeof(glm::vec4);
        vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, 0));

        // Set VBO
        _vbo.setData(vertexData);

        // Set VAO
        _vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);
        _vao.setDrawCount(vertices.size());
        _vao.attachVBO(&_vbo);
    }

}