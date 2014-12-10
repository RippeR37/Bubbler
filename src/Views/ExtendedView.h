#ifndef VIEW_EXTENDED_VIEW_H_INCLUDED
#define VIEW_EXTENDED_VIEW_H_INCLUDED

#include "View.h"
#include "../Utils/GL+/Program.h"
#include "../Utils/GL+/VertexArray.h"
#include "../Utils/GL+/VertexBuffer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace View {

    /***
     * Template class of extended View where type T is View's assigned model
     */

    template<typename T>
    class ExtendedView : public View<T> {
        public:
            virtual ~ExtendedView() {
                
            }
            
            virtual void init(const T& object) {
                initVBO(object);
                initVAO();
            }

        protected:
            virtual void initVAO() {
                _vao.bind();
                    _vbo.bind();
                        _vao.setAttribPointers(_vbo.getAttributes);
                    _vbo.unbind();
                _vao.unbind();
            }

            virtual void initVBO(const T& object) {
                GL::VertexBuffer::Data vertexData = getVertexData(object);

                _vbo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
                _vbo.setTarget(GL::VertexBuffer::Target::Array);

                _vbo.bind();
                _vbo.setData(vertexData);
                _vbo.unbind();

                vertexData.done();
            }

            virtual GL::VertexBuffer::Data getVertexData(const T& object) = 0;

            unsigned int _drawCount;
            GL::Program _program;
            GL::VertexArray _vao;
            GL::VertexBuffer _vbo;
    };

    /***
     * Template specialization of extended View for View's without models
     */

    template<>
    class ExtendedView<void> : public View<void> {
        public:
            virtual ~ExtendedView() {

            }
            
            virtual void init() {
                initVBO();
                initVAO();
            }

        protected:
            virtual void initVAO() {
                _vao.bind();
                    _vbo.bind();
                        _vao.setAttribPointers(_vbo.getAttributes);
                    _vbo.unbind();
                _vao.unbind();
            }

            virtual void initVBO() {
                GL::VertexBuffer::Data vertexData = getVertexData();

                _vbo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
                _vbo.setTarget(GL::VertexBuffer::Target::Array);

                _vbo.bind();
                _vbo.setData(vertexData);
                _vbo.unbind();

                vertexData.done();
            }

            virtual GL::VertexBuffer::Data getVertexData() = 0;

            unsigned int _drawCount;
            GL::Program _program;
            GL::VertexArray _vao;
            GL::VertexBuffer _vbo;
    };

}

#endif