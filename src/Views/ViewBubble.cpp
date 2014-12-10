#include "ViewBubble.h"
#include "../Game.h"
#include "../Models/States.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

namespace View {

    ViewBubble::ViewBubble() {
        _program.load(
            GL::Shader("assets/shaders/bubble.vs", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/bubble.fs", GL::Shader::Type::FragmentShader)
        );
    }

    ViewBubble::~ViewBubble() {

    }

    void ViewBubble::init(const Model::Bubble& bubble) {
        initVBO(bubble);
        initVAO();
    }

    void ViewBubble::render(const Model::Bubble& bubble) {
        static Controller::State::Gameplay& gameplay = *Model::States::get().gameplay;
        static Controller::Camera& camera = gameplay.getCamera();
        static glm::vec3 translation;
        static glm::vec3 camPos;
        static glm::vec3 bubbleCenter;

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

        camera = gameplay.getCamera();
        camPos = camera.getPos3D();
        translation = bubble.getPosition(); 
        bubbleCenter = translation + glm::vec3(bubble.getRadius());

        gameplay.getPipeline().getStack().pushMatrix();

            gameplay.getPipeline().getStack().translate(translation);
            gameplay.getPipeline().getStack().scale(glm::vec3(bubble.getRadius()));

            _program.use();
            _program["MVP"].setMatrix(gameplay.getPipeline().getMVP());
            _program["uColor"].setVec(bubble.getColor());
            _program["uCamPos"].setVec(camPos);
            _program["uBubbleCenter"].setVec(translation);
            _program["uEyeDir"].setVec(camera.getDirection());
            _program["lightbubblePosition"].setVec(lightbubblePosition[0], count);

                _vao.bind();
                    glEnable(GL_CULL_FACE);
                    glDrawArrays(GL_TRIANGLES, 0, _drawCount);
                _vao.unbind();

            _program.unbind();

        gameplay.getPipeline().getStack().popMatrix();
    }

    void ViewBubble::initVAO() {
        _vao.bind();
            _vbo.bind();
                _vao.enableAttrib(0);
                _vao.setAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 2, (const GLvoid*)0);

                _vao.enableAttrib(1);
                _vao.setAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 2, (const GLvoid*)sizeof(glm::vec4));
            _vbo.unbind();
        _vao.unbind();
    }

    void ViewBubble::initVBO(const Model::Bubble& bubble) {
        std::vector<glm::vec4> vertices = getVertices(bubble);

        _vbo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
        _vbo.setTarget(GL::VertexBuffer::Target::Array);

        _vbo.bind();
        _vbo.setData(vertices);
        _vbo.unbind();
    }

    std::vector<glm::vec4> ViewBubble::getVertices(const Model::Bubble& bubble) {
        static const std::string bubbleModlePath = "assets/models/bubble.obj";
        std::vector<glm::vec4> vertices;
        
        std::vector<glm::vec4> objVertices;
        std::vector<glm::vec4> objNormals;

        int res;
        char lineHeader[128];
        FILE* file;

        _drawCount = 0;

        file = fopen(bubbleModlePath.c_str(), "r");
        if(file == nullptr)
            throw new Util::Exception::FatalError("Could not load bubble.obj model!");

        while(true) {
            res = fscanf(file, "%s", lineHeader);
            if(res == EOF)
                break;

            if(strcmp(lineHeader, "v") == 0) {
                glm::vec4 vertex = glm::vec4(1.0f);
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

                objVertices.push_back(vertex);

            } else if(strcmp(lineHeader, "vt") == 0) {
                // ignore tex coords

            } else if(strcmp(lineHeader, "vn") == 0) {
                glm::vec4 normal = glm::vec4(0.0f);
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                objNormals.push_back(normal);

            } else if(strcmp(lineHeader, "f") == 0) {
                std::string v1, v2, v3;
                unsigned int vIndex[3], nIndex[3], tmp;
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
                    &vIndex[0], &tmp, &nIndex[0], 
                    &vIndex[1], &tmp, &nIndex[1], 
                    &vIndex[2], &tmp, &nIndex[2]
                );

                if(matches != 9)
                    std::cerr << "Wrong file format! Matches: " << matches << std::endl;

                vertices.push_back(objVertices[vIndex[0] - 1]);
                vertices.push_back(objNormals[nIndex[0] - 1]);
                
                vertices.push_back(objVertices[vIndex[1] - 1]);
                vertices.push_back(objNormals[nIndex[1] - 1]);

                vertices.push_back(objVertices[vIndex[2] - 1]);
                vertices.push_back(objNormals[nIndex[2] - 1]);

                _drawCount += 3;
            }
        }

        fclose(file);

        return vertices;
    }

}