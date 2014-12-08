#ifndef UTILS_GL_VERTEX_ARRAY_H_INCLUDED
#define UTILS_GL_VERTEX_ARRAY_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GL {

    class VertexArray {
        public:
            VertexArray();
            VertexArray(VertexArray&& vao);
            ~VertexArray();

            VertexArray& operator=(VertexArray&& vao);

            void bind();
            void unbind();

            void enableAttrib(GLuint index);
            void disableAttrib(GLuint index);

            void setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

            GLuint getID() const;

        private:
            VertexArray& operator=(const VertexArray&);
            VertexArray(const VertexArray&);

            void create();
            void destroy();

            GLuint _vaoID;
    };

}

#endif